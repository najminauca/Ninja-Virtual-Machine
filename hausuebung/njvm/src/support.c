#include <stdlib.h>
#include <stdio.h>
#include "njvm.h"
#include "memory.h"

// Helpers for BigInt lib as per support.h

// taken vom bigint/tst/support.c
void fatalError(char *msg) {
    printf("ERROR bip: %s\n", msg);
    error(1);
}

// taken vom bigint/tst/support.c
void * newPrimObject(int dataSize) {
    return createPrimitiveObj(dataSize);
}

// taken vom bigint/tst/support.c
void * getPrimObjectDataPointer(void * obj){
    ObjRef oo = ((ObjRef) (obj));
    return oo->data;
}