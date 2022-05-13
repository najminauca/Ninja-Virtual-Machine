//
// Created by dev on 21.04.22.
//
#include "stdio.h"
#include "njvm.h"

void printProgram() {
    int i = 0;
    while (1) {
        uint32_t ins = programm_speicher[i];
        uint32_t opcode = ins >> 24;
        i = i+1;
        if (opcode == HALT) {
            printf("halt\n");
            break;
        } else if (opcode == PUSHC) {
            printf("pushc %d\n", SIGN_EXTEND(IMM(ins)));
        } else if (opcode == ADD) {
            printf("add\n");
        } else if (opcode == SUB) {
            printf("sub\n");
        } else if (opcode == MUL) {
            printf("mul\n");
        } else if (opcode == DIV) {
            printf("div\n");
        } else if (opcode == MOD) {
            printf("mod\n");
        } else if (opcode == RDINT) {
            printf("rdint\n");
        } else if (opcode == WRINT) {
            printf("wrint\n");
        } else if (opcode == RDCHR) {
            printf("rdchr\n");
        } else if (opcode == WRCHR) {
            printf("wrchr\n");
        } else if (opcode == PUSHG) {
            printf("pushg %d\n", SIGN_EXTEND(IMM(ins)));
        } else if (opcode == POPG) {
            printf("popg %d\n", SIGN_EXTEND(IMM(ins)));
        } else if (opcode == ASF) {
            printf("asf %d\n", SIGN_EXTEND(IMM(ins)));
        } else if (opcode == RSF) {
            printf("rsf %d\n", SIGN_EXTEND(IMM(ins)));
        } else if (opcode == PUSHL) {
            printf("pushl %d\n", SIGN_EXTEND(IMM(ins)));
        } else if (opcode == POPL) {
            printf("popl %d\n", SIGN_EXTEND(IMM(ins)));
        } else {
            printf("Unknown opcode %d at %d.. Aborting\n", opcode,i-1);
            break;
        }
    }
}