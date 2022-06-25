//
// Created by dev on 25.06.22.
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "njvm.h"
#include "memory.h"
#include "bigint.h"

void * heap = NULL;
uint32_t stack_limit;

typedef struct {
    void * start;
    void * end;
} Slab;

Slab slab1;
Slab slab2;

Slab *currentSlab;

void * slabFreePointer;

bool zeroMemoryAfterGc = false;

// statistics
long allocatedBytes = 0;
long allocatedObjects = 0;
long gcRuns = 0;
long gcRunsDueContention = 0;
unsigned long gcFreed = 0;
unsigned long gcReallocBytes = 0;
unsigned long gcReallocObj = 0;

// globals
uint32_t static_data_area_size = 0;
ObjRef *static_data_area;
Stackslot *stack = NULL;

// größen
uint32_t stack_size_bytes = STACK_SIZE_DEFAULT * MEMORY_UNIT;
uint32_t heap_size_bytes = HEAP_SIZE_DEFAULT * MEMORY_UNIT;
uint32_t heap_slab_size;

bool allocationSinceGc = false;
bool printGcStats = false;

void enableGcStatsPrint() {
    printGcStats = true;
}

void set_heap_size(int32_t size_kib) {
    if (heap != NULL) {
        printf("ERROR: Can't change heap size while running!\n");
        error(1);
    }
    heap_size_bytes = size_kib * MEMORY_UNIT;
    heap_slab_size = heap_size_bytes / 2;
}

void set_stack_size(int32_t size_kib) {
    if (stack != NULL) {
        printf("ERROR: Can't change stack size while running!\n");
        error(1);
    }
    stack_size_bytes = size_kib * MEMORY_UNIT;
}

void init_memory() {
    if (heap != NULL || stack != NULL) {
        printf("ERROR: Can't double initialize memory!\n");
        error(1);
    }
    stack = malloc(stack_size_bytes);
    if (stack == NULL) {
        printf("ERROR: Failed to allocate %d bytes for the stack!\n",stack_size_bytes);
        error(1);
    }
    stack_limit = stack_size_bytes / sizeof(Stackslot);
    if (stack_limit < 1) {
        printf("ERROR: Stack byte size < 1\n");
        error(1);
    }

    heap = malloc(heap_size_bytes);
    if (heap == NULL && heap_size_bytes > 0) {
        printf("ERROR: Failed to allocate %d bytes for the heap!\n",heap_size_bytes);
        error(1);
    }
    heap_slab_size = heap_size_bytes / 2;
    slab1.start = heap;
    slab1.end = heap + heap_slab_size;
    slab2.end = heap + heap_size_bytes;
    slab2.start = slab2.end - heap_slab_size;

    if (zeroMemoryAfterGc) {
        memset(heap, 0, heap_size_bytes);
        memset(stack, 0, stack_size_bytes);
    }

    currentSlab = &slab1;
    slabFreePointer = currentSlab->start;
}

void free_all() {
    if (heap != NULL) {
        free(heap);
        heap = NULL;
    }
    if (stack != NULL) {
        free(stack);
        stack = NULL;
    }
}

void enableMemoryZeroing() {
    zeroMemoryAfterGc = true;
}

void * reallocate(ObjRef obj, void ** newFreePointer) {
    if (obj == NULL) {
        return NULL;
    }
    if (obj->brokenHeart) {
        return obj->forwardPointer;
    } else {
        unsigned long size;
        if (IS_PRIMITIVE(obj)) {
            size = sizeof(Obj) + obj->size;
        } else {
            size = sizeof(Obj) + (sizeof(void *) * GET_ELEMENT_COUNT(obj));
        }
        gcReallocObj += 1;
        gcReallocBytes += size;
        memcpy(*newFreePointer, obj,size);
        ObjRef newObj = *newFreePointer;
        obj->brokenHeart = true;
        obj->forwardPointer = *newFreePointer;
        *newFreePointer += size;
        return newObj;
    }
}

void gc() {
    if (debug) {
        printf("Running gc\n");
    }
    void * newFreePointer;
    Slab * newSlab;
    if (currentSlab->start == slab1.start) {
        newSlab = &slab2;
    } else {
        newSlab = &slab1;
    }
    newFreePointer = newSlab->start;
    // reallocate root objects
    rvr = reallocate(rvr, &newFreePointer);
    bip.op1 = reallocate(bip.op1, &newFreePointer);
    bip.op2 = reallocate(bip.op2, &newFreePointer);
    bip.rem = reallocate(bip.rem, &newFreePointer);
    bip.res = reallocate(bip.res, &newFreePointer);

    for (int i = 0; i < static_data_area_size; i++) {
        static_data_area[i] = reallocate(static_data_area[i],&newFreePointer);
    }
    for (int i = 0; i < sp; i++) {
        if (stack[i].isObjRef) {
            stack[i].u.objRef = reallocate(stack[i].u.objRef,&newFreePointer);
        }
    }

    // scan phase
    void * scanPos = newSlab->start;
    while (scanPos < newFreePointer) {
        ObjRef obj = scanPos;
        if (IS_PRIMITIVE(obj)) {
            scanPos += sizeof(ObjRef) + obj->size;
        } else {
            int size = GET_ELEMENT_COUNT(obj);
            for (int i = 0; i < size; i++) {
                GET_REFS_PTR(obj)[i] = reallocate(GET_REFS_PTR(obj)[i], &newFreePointer);
            }
            scanPos += sizeof(ObjRef) + sizeof(void *) * size;
        }
    }

    if (zeroMemoryAfterGc) {
        memset(currentSlab->start, 0, heap_slab_size);
    }
    gcFreed += (slabFreePointer - currentSlab->start) - (newFreePointer - newSlab->start);
    currentSlab = newSlab;
    slabFreePointer = newFreePointer;

    allocationSinceGc = false;
    gcRuns += 1;
    if (printGcStats) {
        printStats();
    }
}


void setObjInt(ObjRef ref, int32_t val) {
    if (ref->size != sizeof(int32_t)) {
        printf("Can't set int of object with size %d!\n", ref->size);
        error(1);
    }
    *(int32_t *) ref->data = val;
}

ObjRef allocate(unsigned int size) {
    if (slabFreePointer + size > currentSlab->end) {
        if (allocationSinceGc) {
            gcRunsDueContention += 1;
            gc();
            return allocate(size);
        } else {
            printf("ERROR: out of memory, tried to allocate %d bytes\n",size);
            error(1);
        }
    }
    allocatedObjects += 1;
    allocatedBytes += size;
    ObjRef obj = slabFreePointer;
    slabFreePointer += size;
    obj->brokenHeart = false;
    obj->forwardPointer = NULL;
    allocationSinceGc = true;
    return obj;
}

/// Create object ObjRef, no raw values
ObjRef createObj(int32_t fields) {
    unsigned int msize = sizeof(Obj) + (fields*sizeof(void *));
    ObjRef obj = allocate(msize);
    int i;
    for (i = 0; i < fields; i++) {
        GET_REFS_PTR(obj)[i] = NULL;
    }
    obj->size = fields;
    obj->size |= MSB;
    return obj;
}

/// Create primitive ObjRef for primitive
ObjRef createPrimitiveObj(int32_t size) {
    unsigned int msize = sizeof(Obj) + size;
    ObjRef obj = allocate(msize);
    obj->size = size;
    return obj;
}

void printStats() {
    printf("Gargabe Collector, stats since last run:\n");
    printf("\tAllocated Bytes \t %ld\n",allocatedBytes);
    printf("\tAllocated Objects \t %ld\n",allocatedObjects);
    printf("\tAmount GC runs \t %ld\n",gcRuns);
    printf("\tMemory shortage runs \t %ld\n",gcRunsDueContention);
    printf("\tGC memory freed \t %ld\n",gcFreed);
    printf("\tGC obj reallocated \t %ld\n", gcReallocObj);
    printf("\tGC bytes reallocated \t %ld\n",gcReallocBytes);
    allocatedBytes = 0;
    allocatedObjects = 0;
    gcRunsDueContention = 0;
    gcFreed = 0;
    gcReallocObj = 0;
    gcReallocBytes = 0;

}

/// Directly call bigint lib to convert from int32, return result
ObjRef createIntObj(int32_t value) {
    bigFromInt(value);
    return bip.res;
}

/// Pop ObjRef of any kind
int popObjRef(ObjRef *ret) {
    if (sp > 0) { // TODO: check for invalid pop over stackframe
        sp = sp - 1;
        if (!stack[sp].isObjRef) {
            printf("Error: Tried to pop objref on int! stack pointer %d\n", sp);
            return 2;
        }
        *ret = stack[sp].u.objRef;
        stack[sp].u.objRef = NULL;
        return 0;
    } else {
        printf("Error: Tried to pop on stack pointer %d\n", sp);
        return 2;
    }
}

/// Pop ObjRef with int primitive value
int popObjRefInt(ObjRef *ret) {
    if (popObjRef(ret) != 0){
        return 1;
    }
    if (!IS_PRIMITIVE(*ret)) {
        printf("Error: Tried to pop primitive on obj");
        return 1;
    }
    return 0;
}

/// Pop ObjRef with obj value
int popObjRefObj(ObjRef *ret) {
    if (popObjRef(ret) != 0){
        return 1;
    }
    if (IS_PRIMITIVE(*ret)) {
        printf("Error: Tried to pop obj on primitive obj");
        return 1;
    }
    return 0;
}

int popInt(int32_t *ret) {
    if (sp > 0) { // TODO: check for invalid pop over stackframe
        sp = sp - 1;
        if (stack[sp].isObjRef) {
            printf("Tried to pop int on objref! stack pointer %d\n", sp);
            return 2;
        }
        *ret = stack[sp].u.number;
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = NULL;
        return 0;
    } else {
        printf("Tried to pop on stack pointer %d\n", sp);
        return 2;
    }
}

int pushObjRef(ObjRef val) {
    if (sp > stack_limit) {
        printf("Tried to pushObjRef over stack limit\n");
        return 2;
    } else {
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = val;
        sp = sp + 1;
        return 0;
    }
}

int pushInt(int32_t val) {
    if (sp > stack_limit) {
        printf("Tried to pushObjRef over stack limit\n");
        return 2;
    } else {
        stack[sp].isObjRef = false;
        stack[sp].u.number = val;
        sp = sp + 1;
        return 0;
    }
}