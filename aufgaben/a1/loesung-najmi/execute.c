#include <stdio.h>
#include "execute.h"
#include "operations.h"

void printNum(int i) {
    if(i < 10) {
        printf("00%d:	", i);
    } else if(i < 100) {
        printf("0%d:	", i);
    } else {
        printf("%d:	", i);
    }
}

void execute(unsigned int ir) {
    int opcode = (ir >> 24);
    int immediate = SIGN_EXTEND(IMMEDIATE(ir));
    if(opcode == PUSHC) {
        pushc(immediate);
    }
    else if(opcode == ADD) {
        add();
    }
    else if(opcode == SUB) {
        sub();
    }
    else if(opcode == MUL) {
        mul();
    }
    else if(opcode == DIV) {
        divnjvm();
    }
    else if(opcode == MOD) {
        mod();
    }
    else if(opcode == RDINT) {
        rdint();
    }
    else if(opcode == WRINT) {
        wrint();
    }
    else if(opcode == RDCHR) {
        rdchr();
    }
    else if(opcode == WRCHR) {
        wrchr();
    }
}

void listProg(unsigned int ir, int pc) {
    int opcode = (ir >> 24);
    int immediate = SIGN_EXTEND(IMMEDIATE(ir));
    printNum(pc);
    if(opcode == HALT) {
        printf("halt\n");
    }
    else if(opcode == PUSHC) {
        printf("pushc   %d\n", immediate);
    }
    else if(opcode == ADD) {
        printf("add\n");
    }
    else if(opcode == SUB) {
        printf("sub\n");
    }
    else if(opcode == MUL) {
        printf("mul\n");
    }
    else if(opcode == DIV) {
        printf("div\n");
    }
    else if(opcode == MOD) {
        printf("mod\n");
    }
    else if(opcode == RDINT) {
        printf("rdint\n");
    }
    else if(opcode == WRINT) {
        printf("wrint\n");
    }
    else if(opcode == RDCHR) {
        printf("rdchr\n");
    }
    else if(opcode == WRCHR) {
        printf("wrchr\n");
    }
}