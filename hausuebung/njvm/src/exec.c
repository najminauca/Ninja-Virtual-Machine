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

int execute(uint32_t ins) {
    uint32_t dec_ins = ins >> 24;
    int32_t imm = SIGN_EXTEND(IMM(ins));
    // switch wäre nett, aber erlaubt keine variabeln deklaration..
    // was wiederum sehr unsauber ist
    switch (dec_ins) {
        case HALT:
            //printf("Found halt instruction\n");
            return 0;
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
        case NEW:
            if (new(imm)) {
                return 2;
            }
            break;
        case GETF:
            if (getf(imm)) {
                return 2;
            }
            break;
        case PUTF:
            if (putf(imm)) {
                return 2;
            }
            break;
        case NEWA:
            if (newa()) {
                return 2;
            }
            break;
        case GETFA:
            if (getfa()) {
                return 2;
            }
            break;
        case PUTFA:
            if (putfa()) {
                return 2;
            }
            break;
        case GETSZ:
            if (getsz()) {
                return 2;
            }
            break;
        case PUSHN:
            if (pushn()) {
                return 2;
            }
            break;
        case REFEQ:
            if (refeq()) {
                return 2;
            }
            break;
        case REFNE:
            if (refne()) {
                return 2;
            }
            break;
        default:
            printf("Found unknown op code %d\n", dec_ins);
            return 2;
    }

    return -1;
}

