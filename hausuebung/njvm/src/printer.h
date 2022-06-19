//
// Created by Aron Heinecke on 21.04.22.
//

#ifndef KSP_PUBLIC_PRINTER_H
#define KSP_PUBLIC_PRINTER_H
void printInstruction(int i, uint32_t ins);
void printProgram();
void printStack();
void printStatics();
void printObjRef(ObjRef ref, int full);
#endif //KSP_PUBLIC_PRINTER_H
