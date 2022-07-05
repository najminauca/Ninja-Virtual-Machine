#ifndef GARBAGE_H
#define GARBAGE_H

typedef struct {
    void *start;
    void *end;
} HeapHalf;

extern void *heap;
extern HeapHalf half1;
extern HeapHalf half2;
extern HeapHalf *currentHalf;
extern void *freePointer;
extern bool purge;
extern bool stats;
extern int stack_n;
extern int heap_n;

void allocateHeap();

void allocateStack();

#endif
