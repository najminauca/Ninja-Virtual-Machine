//
// Created by Aron Heinecke on 21.04.22.
//
#include "stdio.h"
#include "njvm.h"
#include "bigint.h"
#include "memory.h"

void printInstruction(int i, uint32_t ins) {
    uint32_t opcode = ins >> 24;
    printf("%04d:\t", i);
    switch (opcode) {
        case HALT:
            printf("halt\n");
            break;
        case PUSHC:
            printf("pushc\t%d\n", SIGN_EXTEND(IMM(ins)));
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
            printf("pushg\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case POPG:
            printf("popg\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case ASF:
            printf("asf\t%d\n", SIGN_EXTEND(IMM(ins)));
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
            printf("eq\n");
            break;
        case NE:
            printf("ne\n");
            break;
        case LT:
            printf("lt\n");
            break;
        case LE:
            printf("le\n");
            break;
        case GT:
            printf("gt\n");
            break;
        case GE:
            printf("ge\n");
            break;
        case JMP:
            printf("jmp\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case BRF:
            printf("brf\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case BRT:
            printf("brt\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case CALL:
            printf("call\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case RET:
            printf("ret\n");
            break;
        case DROP:
            printf("drop\t%d\n", SIGN_EXTEND(IMM(ins)));
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
        case NEW:
            printf("new\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case GETF:
            printf("getf\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case PUTF:
            printf("putf\t%d\n", SIGN_EXTEND(IMM(ins)));
            break;
        case NEWA:
            printf("newa\n");
            break;
        case GETFA:
            printf("getfa\n");
            break;
        case PUTFA:
            printf("putfa\n");
            break;
        case GETSZ:
            printf("getsz\n");
            break;
        case PUSHN:
            printf("pushn\n");
            break;
        case REFEQ:
            printf("refeq\n");
            break;
        case REFNE:
            printf("refne\n");
            break;
        default:
            printf("Unknown opcode %d at %d.. Aborting\n", opcode, i - 1);
            break;
    }
}

void printProgram() {
    int i = 0;
    for (i = 0; i < programm_size; i++) {
        printInstruction(i, programm_speicher[i]);
    }
}

/// ObjRef printing, set full to true for multi-line recursive resolution
void printObjRef(ObjRef ref, int full) {
    if (ref == NULL) {
        printf("null\n");
        return;
    }
    if (IS_PRIMITIVE(ref)) {
        if (ref->size == sizeof(int32_t)) {
            printf("size: %d, data: (int) %d", ref->size, *(int *) ref->data);
        } else {
            printf("size: %d, data: (bigint) ", ref->size);
            bip.op1 = ref;
            bigPrint(stdout);
        }
        if (full) {
            printf(",\n");
        } else {
            printf("\n");
        }
    } else {
        int size = GET_ELEMENT_COUNT(ref);
        printf("size: %d, data: (objref) [", size);
        if (full) {
            printf("\n");
        }
        int i;
        for (i = 0; i < size; i++) {
            ObjRef val = GET_REFS_PTR(ref)[i];
            if (!full && i > 0) {
                printf(",");
            }
            if (val != NULL) {
                if (full) {
                    printObjRef(val, true);
                } else {
                    printf("%p", (void *) val);
                }
            } else {
                printf("null,\n");
            }
        }
        printf("]\n");
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
            printf("%d:\tObjref: %p ", i, (void *) stack[i].u.objRef);
            printObjRef(stack[i].u.objRef, false);
        } else {
            printf("%d:\t%d\n", i, stack[i].u.number);
        }
    }
}

void printStatics() {
    int i;
    for (i = 0; i < static_data_area_size; i++) {
        printf("%d:\t", i);
        printObjRef(static_data_area[i], false);
    }
}