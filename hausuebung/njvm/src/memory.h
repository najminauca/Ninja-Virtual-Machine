//
// Created by dev on 25.06.22.
//

#ifndef NJVM_MEMORY_H
#define NJVM_MEMORY_H

#include <stdint-gcc.h>
#include "njvm.h"

#define STACK_SIZE_DEFAULT 64
#define HEAP_SIZE_DEFAULT 8192
#define MEMORY_UNIT 1024

// globale variabeln
extern uint32_t static_data_area_size;
extern ObjRef *static_data_area;
extern Stackslot *stack;

// größen
extern uint32_t static_data_area_size;

void set_heap_size(int32_t size_kib);
void set_stack_size(int32_t size_kib);

// zugriffsfunktionen
int popInt(int32_t *);
int popObjRef(ObjRef *ret);
int popObjRefInt(ObjRef *ret);
int popObjRefObj(ObjRef *ret);

int pushObjRef(ObjRef val);
int pushInt(int32_t val);

ObjRef createIntObj(int32_t value);
ObjRef createObj(int32_t fields);

void enableMemoryZeroing();

// garbage collection
void gc();
void init_memory();
void free_all();
void printStats();

#endif //NJVM_MEMORY_H
