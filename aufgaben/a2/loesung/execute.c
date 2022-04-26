#include <stdio.h>
#include "execute.h"
#include "operations.h"

void printNum(int i) {
    if(i < 10) {
        printf("00%d:\t", i);
    } else if(i < 100) {
        printf("0%d:\t", i);
    } else {
        printf("%d:\t", i);
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
    else if(opcode == PUSHG) {
        pushg(immediate);
    }
    else if(opcode == POPG) {
        popg(immediate);
    }
    else if(opcode == ASF) {
        asf(immediate);
    }
    else if(opcode == RSF) {
        rsf();
    }
    else if(opcode == PUSHL) {
        pushl(immediate);
    }
    else if(opcode == POPL) {
        popl(immediate);
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
        printf("pushc\t%d\n", immediate);
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
    else if(opcode == PUSHG) {
        printf("pushg\t%d\n", immediate);
    }
    else if(opcode == POPG) {
        printf("popg\t%d\n", immediate);
    }
    else if(opcode == ASF) {
        printf("asf\t%d\n", immediate);
    }
    else if(opcode == RSF) {
        printf("rsf\n");
    }
    else if(opcode == PUSHL) {
        printf("pushl\t%d\n", immediate);
    }
    else if(opcode == POPL) {
        printf("popl\t%d\n", immediate);
    }  
}