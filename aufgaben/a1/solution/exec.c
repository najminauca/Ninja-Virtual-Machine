//
// Created by dev on 21.04.22.
//
#include "stdio.h"
#include "stdint.h"
#include "njvm.h"

int pop(int32_t* ret) {
    if (sp > 0) {
        *ret = stack[sp];
        sp = sp-1;
        return 0;
    } else {
        printf("Tried to pop on stack pointer %d\n",sp);
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
    if(dec_ins == HALT) {
        printf("Found halt instruction\n");
        return 1;
    } else if(dec_ins == PUSHC ) {
        int32_t imm = SIGN_EXTEND(ins & 0x00FFFFFF);
        if (push(imm) != 0) {
            return 1;
        }
    } else if(dec_ins == ADD || dec_ins == SUB || dec_ins == MUL || dec_ins == DIV || dec_ins == MOD) {
        int32_t a, b, r;
        if (pop(&b) != 0)
            return 1;
        if (pop(&a) != 0)
            return 1;
        if (dec_ins == ADD) {
            r = a + b;
        } else if (dec_ins == SUB) {
            r = a - b;
        } else if (dec_ins == MUL) {
            r = a * b;
        } else if (dec_ins == DIV) {
            r = a / b;
        } else if (dec_ins == MOD) {
            r = a % b;
        } else {
            printf("Unreachable case for arithmetics!");
            return 1;
        }
        if (push(r) != 0) {
            return 1;
        }
    } else if(dec_ins == RDINT ) {
        int32_t in = 0;
        scanf("%d", &in);
        if (push(in) != 0) {
            return 1;
        }
    } else if(dec_ins == WRINT ) {
        int32_t v;
        if (pop(&v) != 0)
            return 1;
        printf("%d",v);
    } else if(dec_ins == RDCHR ) {
        char in = 0;
        scanf("%c", &in);
        if (push((int32_t) in) != 0) {
            return 1;
        }
    } else if(dec_ins == WRCHR ) {
        int32_t v;
        if (pop(&v) != 0)
            return 1;
        printf("%c",(char)v);
    } else {
        printf("Found unknown op code %d\n",dec_ins);
        return 1;
    }

    return 0;
}

