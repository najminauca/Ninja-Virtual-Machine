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
    switch(opcode) {
        case PUSHC:
            pushc(immediate);
            break;
        case ADD:
            add();
            break;
        case SUB:
            sub();
            break;
        case MUL:
            mul();
            break;
        case DIV:
            divnjvm();
            break;
        case MOD:
            mod();
            break;
        case RDINT:
            rdint();
            break;
        case WRINT:
            wrint();
            break;
        case RDCHR:
            rdchr();
            break;
        case WRCHR:
            wrchr();
            break;
        case PUSHG:
            pushg(immediate);
            break;
        case POPG:
            popg(immediate); 
            break;  
        case ASF:
            asf(immediate);
            break;
        case RSF:
            rsf();
            break;
        case PUSHL:
            pushl(immediate);
            break;
        case POPL:
            popl(immediate);
            break;
        case EQ:
            eq();
            break;
        case NE:
            ne();
            break;
        case LT:
            lt();
            break;
        case LE:
            le();
            break;
        case GT:
            gt();
            break;
        case GE:
            ge();
            break;
        case JMP:
            jmp(immediate);
            break;
        case BRF:
            brf(immediate);
            break;
        case BRT: 
            brt(immediate);    
    }
}

void listProg(unsigned int ir, int pc) {
    int opcode = (ir >> 24);
    int immediate = SIGN_EXTEND(IMMEDIATE(ir));
    printNum(pc);
    switch(opcode) {
        case HALT:
            printf("halt\n");
            break;
        case PUSHC:
            printf("pushc\t%d\n", immediate);
            break;
        case ADD:
            printf("add\n");
            break;
        case SUB:
            printf("sub\n");
            break;
        case MUL:
            printf("mul\n");
            break;
        case DIV:
            printf("div\n");
            break;
        case MOD:
            printf("mod\n");
            break;
        case RDINT:
            printf("rdint\n");
            break;
        case WRINT:
            printf("wrint\n");
            break;
        case RDCHR:
            printf("rdchr\n");
            break;
        case WRCHR:
            printf("wrchr\n");
            break;
        case PUSHG:
            printf("pushg\t%d\n", immediate);
            break;
        case POPG:
            printf("popg\t%d\n", immediate);
            break;  
        case ASF:
            printf("asf\t%d\n", immediate);
            break;
        case RSF:
            printf("rsf\n");
            break;
        case PUSHL:
            printf("pushl\t%d\n", immediate);
            break;
        case POPL:
            printf("popl\t%d\n", immediate);
            break;
        case EQ:
            printf("eq\t\n");
            break;
        case NE:
            printf("ne\t\n");
            break;
        case LT:
            printf("lt\t\n");
            break;
        case LE:
            printf("le\t\n");
            break;
        case GT:
            printf("gt\t\n");
            break;
        case GE:
            printf("ge\t\n");
            break;
        case JMP:
            printf("jmp\t%d\n", immediate);
            break;
        case BRF:
            printf("brf\t%d\n", immediate);
            break;
        case BRT: 
            printf("brt\t%d\n", immediate);   
    }
}