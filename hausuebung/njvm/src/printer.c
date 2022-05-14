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
        printf("%03d ", i);
        i = i + 1;
        switch (opcode) {
            case HALT:
                printf("halt\n");
                run = 0;
                break;
            case PUSHC:
                printf("pushc %d\n", SIGN_EXTEND(IMM(ins)));
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
                printf("pushg %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case POPG:
                printf("popg %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case ASF:
                printf("asf %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case RSF:
                printf("rsf %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case PUSHL:
                printf("pushl %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case POPL:
                printf("popl %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case EQ:
                printf("EQ\n");
                break;
            case NE:
                printf("NE\n");
                break;
            case LT:
                printf("LT\n");
                break;
            case LE:
                printf("LE\n");
                break;
            case GT:
                printf("GT\n");
                break;
            case GE:
                printf("GE\n");
                break;
            case JMP:
                printf("JMP %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case BRF:
                printf("BRF %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            case BRT:
                printf("BRT %d\n", SIGN_EXTEND(IMM(ins)));
                break;
            default:
                printf("Unknown opcode %d at %d.. Aborting\n", opcode, i - 1);
                run = 0;
        }
    }
}