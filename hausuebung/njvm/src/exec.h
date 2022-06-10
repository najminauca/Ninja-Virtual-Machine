//
// Created by Aron Heinecke on 21.04.22.
//

#ifndef KSP_PUBLIC_EXEC_H
#define KSP_PUBLIC_EXEC_H

int execute(uint32_t ins);

int popInt(int32_t *);
int popObjRef(ObjRef *ret);

int pushObjRef(ObjRef val);
int pushInt(int32_t val);

ObjRef createIntObj(int32_t value);
int32_t getObjInt(ObjRef ref);
void setObjInt(ObjRef ref, int32_t val);

#endif //KSP_PUBLIC_EXEC_H
