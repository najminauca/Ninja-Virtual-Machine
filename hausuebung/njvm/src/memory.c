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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpointer-arith"

void * heap = NULL;
uint32_t stack_limit;

typedef struct {
    void * start;
    void * end;
} Slab;

Slab slab1;
Slab slab2;

Slab *currentBank;

void * bankFreePointer;

bool zeroMemoryAfterGc = false;

// statistics
long allocatedBytes = 0;
long allocatedObjects = 0;
long gcRuns = 0;
long gcRunsDueContention = 0;

// globals
uint32_t static_data_area_size = 0;
ObjRef *static_data_area;
Stackslot *stack = NULL;

// größen
uint32_t stack_size_bytes = STACK_SIZE_DEFAULT * MEMORY_UNIT;
uint32_t heap_size_bytes = HEAP_SIZE_DEFAULT * MEMORY_UNIT;
uint32_t heap_slab_size;

int allocationSinceGc = false;

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

    currentBank = &slab1;
    bankFreePointer = currentBank->start;
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

void gc() {
    //TODO

    if (zeroMemoryAfterGc) {
        memset(currentBank->start,0,heap_slab_size);
    }

    allocationSinceGc = false;
}


void setObjInt(ObjRef ref, int32_t val) {
    if (ref->size != sizeof(int32_t)) {
        printf("Can't set int of object with size %d!\n", ref->size);
        error(1);
    }
    *(int32_t *) ref->data = val;
}

/// Create object ObjRef, no raw values
ObjRef createObj(int32_t fields) {
    unsigned int msize = sizeof(uint32_t) + fields*sizeof(int32_t);
    if (bankFreePointer + msize > currentBank->end) {
        if (!allocationSinceGc) {
            gcRunsDueContention += 1;
            gc();
            return createObj(fields);
        } else {
            printf("ERROR: out of memory, tried to allocate %d bytes",msize);
            error(1);
        }
    }
    allocatedObjects += 1;
    allocatedBytes += msize;
    ObjRef obj = bankFreePointer;
    bankFreePointer += msize;
    int i;
    for (i = 0; i < fields; i++) {
        GET_REFS_PTR(obj)[i] = NULL;
    }
    obj->size = fields;
    obj->size |= MSB;
    allocationSinceGc = true;
    return obj;
}

void printStats() {
    printf("Allocated Bytes \t %ld\n",allocatedBytes);
    printf("Allocated Objects \t %ld\n",allocatedObjects);
    printf("Amount GC runs \t %ld\n",gcRuns);
    printf("Memory shortage runs \t %ld\n",gcRunsDueContention);
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
#pragma clang diagnostic pop