/*
 * support.c -- support functions for big integer library
 */


#include <stdio.h>
#include <stdlib.h>
#include "njvm.h"
#include "garbage.h"


/*
 * This routine is called in case a fatal error has occurred.
 * It should print the error message and terminate the program.
 */
void fatalError(char *msg) {
  printf("Fatal error: %s\n", msg);
  exit(1);
}


/*
 * This function is called whenever a new primitive object with
 * a certain amount of internal memory is needed. It should return
 * an object reference to a regular object, which contains a freely
 * usable memory area of at least the requested size (measured in
 * bytes). The memory area need not be initialized in any way.
 *
 * Note that this function may move all objects in memory at will
 * (due to, e.g., garbage collection), as long as the pointers in
 * the global "bip" structure point to the correct objects when
 * the function returns.
 */
void * newPrimObject(int dataSize) {
  ObjRef bigObjRef;

  unsigned int msize = sizeof(Obj) + dataSize;
  bigObjRef = allocateObj(msize);

  if (bigObjRef == NULL) {
    fatalError("newPrimObject() got no memory");
  }
  
  bigObjRef->size = dataSize;
  return bigObjRef;
}

void * getPrimObjectDataPointer(void * obj){
    ObjRef oo = ((ObjRef)  (obj));
    return oo->data;
}

