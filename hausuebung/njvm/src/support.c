#include <stdlib.h>
#include <stdio.h>
#include "njvm.h"

// Helpers for BigInt lib as per support.h

// taken vom bigint/tst/support.c
void fatalError(char *msg) {
    printf("Fatal error: %s\n", msg);
    exit(1);
}

// taken vom bigint/tst/support.c
void * newPrimObject(int dataSize) {
    ObjRef bigObjRef;

    bigObjRef = malloc(sizeof(unsigned int) +
                       dataSize * sizeof(unsigned char));
    if (bigObjRef == NULL) {
        fatalError("newPrimObject() got no memory");
    }
    bigObjRef->size = dataSize;
    return bigObjRef;
}

// taken vom bigint/tst/support.c
void * getPrimObjectDataPointer(void * obj){
    ObjRef oo = ((ObjRef) (obj));
    return oo->data;
}