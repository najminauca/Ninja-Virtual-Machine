//
// Created by Aron Heinecke on 21.04.22.
//
#include <stdint.h>
#include <stdio.h>
#include "njvm.h"
#include "instruction.h"

int pop(int32_t *ret) {
    if (sp > 0) { // TODO: check for invalid pop over stackframe
        sp = sp - 1;
        *ret = stack[sp];
        return 0;
    } else {
        printf("Tried to pop on stack pointer %d\n", sp);
        return 1;
    }
}

int push(int32_t val) {
    if (sp > STACK_LIMIT) {
        printf("Tried to push over stack limit\n");
        return 1;
    } else {
        stack[sp] = val;
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
            printf("Found halt instruction\n");
            return 1;
            break;
        case PUSHC:
            if (push(imm) != 0) {
                return 1;
            }
            break;
        case ADD:
            if (add()) {
                return 1;
            }
            break;
        case SUB:
            if (sub()) {
                return 1;
            }
            break;
        case MUL:
            if (mul()) {
                return 1;
            }
            break;
        case DIV:
            if (div()) {
                return 1;
            }
            break;
        case MOD:
            if (mod()) {
                return 1;
            }
            break;
        case RDINT:
            if (rdint()) {
                return 1;
            }
            break;
        case WRINT:
            if (wrint()) {
                return 1;
            }
            break;
        case RDCHR:
            if (rdchr()) {
                return 1;
            }
            break;
        case WRCHR:
            if (wrchr()) {
                return 1;
            }
            break;
        case PUSHG:
            if (pushg(imm)) {
                return 1;
            }
            break;
        case POPG:
            if (popg(imm)) {
                return 1;
            }
            break;
        case ASF:
            if (asf(imm)) {
                return 1;
            }
            break;
        case RSF:
            if (rsf()) {
                return 1;
            }
            break;
        case PUSHL:
            if (pushl(imm)) {
                return 1;
            }
            break;
        case POPL:
            if (popl(imm)) {
                return 1;
            }
            break;
        case EQ:
            if (eq()) {
                return 1;
            }
            break;
        case NE:
            if (ne()) {
                return 1;
            }
            break;
        case LT:
            if (lt()) {
                return 1;
            }
            break;
        case LE:
            if (le()) {
                return 1;
            }
            break;
        case GT:
            if (gt()) {
                return 1;
            }
            break;
        case GE:
            if (ge()) {
                return 1;
            }
            break;
        case JMP:
            if (jmp(imm)) {
                return 1;
            }
            break;
        case BRF:
            if (brf(imm)) {
                return 1;
            }
            break;
        case BRT:
            if (brt(imm)) {
                return 1;
            }
            break;
        case CALL:
            if (call(imm)) {
                return 1;
            }
            break;
        case RET:
            if (ret()) {
                return 1;
            }
            break;
        case DROP:
            if (drop(imm)) {
                return 1;
            }
            break;
        case PUSHR:
            if (pushr()) {
                return 1;
            }
            break;
        case POPR:
            if (popr()) {
                return 1;
            }
            break;
        case DUP:
            if (dup()) {
                return 1;
            }
            break;
        default:
            printf("Found unknown op code %d\n", dec_ins);
            return 1;
    }

    return 0;
}

