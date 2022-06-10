//
// Created by Aron Heinecke on 21.04.22.
//
#include "stdio.h"
#include "njvm.h"

void printInstruction(int i, uint32_t ins) {
    uint32_t opcode = ins >> 24;
    printf("%04d\t", i);
    switch (opcode) {
        case HALT:
            printf("halt\t\n");
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
            printf("c_div\t\n");
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
            printf("rsf\n");
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
        case CALL:
            printf("call \t%04d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case RET:
            printf("ret\n");
            break;
        case DROP:
            printf("drop \t%04d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case PUSHR:
            printf("pushr\n");
            break;
        case POPR:
            printf("popr\n");
            break;
        case DUP:
            printf("dup\n");
            break;
        default:
            printf("Unknown opcode %d at %d.. Aborting\n", opcode, i - 1);
            break;
    }
}

void printProgram() {
    int i = 0;
    for (i = 0; i < programm_size; i++) {
        printInstruction(i,programm_speicher[i]);
    }
}

void printObjRef(ObjRef ref) {
    if (ref->size == sizeof(int32_t)) {
        printf("size: %d, data: (int) %d\n",ref->size,*(int*)ref->data);
    } else {
        printf("size: %d, data: ",ref->size);
        int i;
        for (i=0; i < ref->size; i++) {
            printf("%x",ref->data[i]);
        }
        printf("\n");
    }
}

void printStack() {
    int i;
    for (i = sp; i >= 0; i--) {
        if (fp == i) {
            printf("fp\t->\t");
        } else {
            printf("\t\t");
        }
        if (stack[i].isObjRef) {
            printf("%04d:\tObjref: ", i);
            printObjRef(stack[i].objRef);
        } else {
            printf("%04d:\t%d\n", i, stack[i].number);
        }
    }
}

void printStatics() {
    int i;
    for(i = 0; i < static_data_area_size; i++) {
        printf("%04d:\t",i);
        printObjRef(static_data_area[i]);
    }
}