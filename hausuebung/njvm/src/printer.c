//
// Created by Aron Heinecke on 21.04.22.
//
#include "stdio.h"
#include "njvm.h"

void printProgram() {
    int i = 0;
    int run = 1;
    while (run) {
        uint32_t ins = programm_speicher[i];
        uint32_t opcode = ins >> 24;
        printf("%04d\t", i);
        i = i + 1;
        switch (opcode) {
            case HALT:
                printf("halt\t\n");
                run = 0;
                break;
            case PUSHC:
                printf("pushc\t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case ADD:
                printf("add\t\n");
                break;
            case SUB:
                printf("sub\t\n");
                break;
            case MUL:
                printf("mul\t\n");
                break;
            case DIV:
                printf("div\t\n");
                break;
            case MOD:
                printf("mod\t\n");
                break;
            case RDINT:
                printf("rdint\t\n");
                break;
            case WRINT:
                printf("wrint\t\n");
                break;
            case RDCHR:
                printf("rdchr\t\n");
                break;
            case WRCHR:
                printf("wrchr\t\n");
                break;
            case PUSHG:
                printf("pushg\t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case POPG:
                printf("popg\t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case ASF:
                printf("asf \t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case RSF:
                printf("rsf \t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case PUSHL:
                printf("pushl\t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case POPL:
                printf("popl\t%d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case EQ:
                printf("eq  \t\n");
                break;
            case NE:
                printf("ne  \t\n");
                break;
            case LT:
                printf("lt  \t\n");
                break;
            case LE:
                printf("le  \t\n");
                break;
            case GT:
                printf("gt  \t\n");
                break;
            case GE:
                printf("ge  \t\n");
                break;
            case JMP:
                printf("jmp \t%04d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case BRF:
                printf("brf \t%04d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case BRT:
                printf("brt \t%04d\n", SIGN_EXTEND(IMM(ins)));
                break;
            default:
                printf("Unknown opcode %d at %d.. Aborting\n", opcode, i - 1);
                run = 0;
        }
    }
}