//
// Created by Aron Heinecke on 21.04.22.
//
#include <stdint.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "njvm.h"
#include "instruction.h"
#include "bigint.h"

void setObjInt(ObjRef ref, int32_t val) {
    if (ref->size != sizeof(int32_t)) {
        printf("Can't set int of object with size %d!\n", ref->size);
        exit(1);
    }
    *(int32_t *) ref->data = val;
}

/// Directly call bigint lib to convert from int32, return result
ObjRef createIntObj(int32_t value) {
//    unsigned int msize = sizeof(uint32_t) + sizeof(int32_t);
//    if ((intObject = malloc(msize)) == NULL) {
//        printf("Failed to allocate int object!\n");
//        exit(1);
//    }
//    intObject->size = sizeof(int32_t);
//    *(int *) intObject->data = value;
    bigFromInt(value);
    return bip.res;
}

int popObjRef(ObjRef *ret) {
    if (sp > 0) { // TODO: check for invalid pop over stackframe
        sp = sp - 1;
        if (!stack[sp].isObjRef) {
            printf("Tried to pop objref on int! stack pointer %d\n", sp);
            return 2;
        }
        *ret = stack[sp].u.objRef;
        return 0;
    } else {
        printf("Tried to pop on stack pointer %d\n", sp);
        return 2;
    }
}

int popInt(int32_t *ret) {
    if (sp > 0) { // TODO: check for invalid pop over stackframe
        sp = sp - 1;
        if (stack[sp].isObjRef) {
            printf("Tried to pop int on objref! stack pointer %d\n", sp);
            return 2;
        }
        *ret = stack[sp].u.number;
        return 0;
    } else {
        printf("Tried to pop on stack pointer %d\n", sp);
        return 2;
    }
}

int pushObjRef(ObjRef val) {
    if (sp > STACK_LIMIT) {
        printf("Tried to pushObjRef over stack limit\n");
        return 2;
    } else {
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = val;
        sp = sp + 1;
        return 0;
    }
}

int pushInt(int32_t val) {
    if (sp > STACK_LIMIT) {
        printf("Tried to pushObjRef over stack limit\n");
        return 2;
    } else {
        stack[sp].isObjRef = false;
        stack[sp].u.number = val;
        sp = sp + 1;
        return 0;
    }
}

int execute(uint32_t ins) {
    uint32_t dec_ins = ins >> 24;
    int32_t imm = SIGN_EXTEND(IMM(ins));
    // switch wäre nett, aber erlaubt keine variabeln deklaration..
    // was wiederum sehr unsauber ist
    switch (dec_ins) {
        case HALT:
            //printf("Found halt instruction\n");
            return 1;
            break;
        case PUSHC:
            if (pushc(imm)) {
                return 2;
            }
            break;
        case ADD:
            if (add()) {
                return 2;
            }
            break;
        case SUB:
            if (sub()) {
                return 2;
            }
            break;
        case MUL:
            if (mul()) {
                return 2;
            }
            break;
        case DIV:
            if (c_div()) {
                return 2;
            }
            break;
        case MOD:
            if (mod()) {
                return 2;
            }
            break;
        case RDINT:
            if (rdint()) {
                return 2;
            }
            break;
        case WRINT:
            if (wrint()) {
                return 2;
            }
            break;
        case RDCHR:
            if (rdchr()) {
                return 2;
            }
            break;
        case WRCHR:
            if (wrchr()) {
                return 2;
            }
            break;
        case PUSHG:
            if (pushg(imm)) {
                return 2;
            }
            break;
        case POPG:
            if (popg(imm)) {
                return 2;
            }
            break;
        case ASF:
            if (asf(imm)) {
                return 2;
            }
            break;
        case RSF:
            if (rsf()) {
                return 2;
            }
            break;
        case PUSHL:
            if (pushl(imm)) {
                return 2;
            }
            break;
        case POPL:
            if (popl(imm)) {
                return 2;
            }
            break;
        case EQ:
            if (eq()) {
                return 2;
            }
            break;
        case NE:
            if (ne()) {
                return 2;
            }
            break;
        case LT:
            if (lt()) {
                return 2;
            }
            break;
        case LE:
            if (le()) {
                return 2;
            }
            break;
        case GT:
            if (gt()) {
                return 2;
            }
            break;
        case GE:
            if (ge()) {
                return 2;
            }
            break;
        case JMP:
            if (jmp(imm)) {
                return 2;
            }
            break;
        case BRF:
            if (brf(imm)) {
                return 2;
            }
            break;
        case BRT:
            if (brt(imm)) {
                return 2;
            }
            break;
        case CALL:
            if (call(imm)) {
                return 2;
            }
            break;
        case RET:
            if (ret()) {
                return 2;
            }
            break;
        case DROP:
            if (drop(imm)) {
                return 2;
            }
            break;
        case PUSHR:
            if (pushr()) {
                return 2;
            }
            break;
        case POPR:
            if (popr()) {
                return 2;
            }
            break;
        case DUP:
            if (dup()) {
                return 2;
            }
            break;
        default:
            printf("Found unknown op code %d\n", dec_ins);
            return 2;
    }

    return 0;
}

