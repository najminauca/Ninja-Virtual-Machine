//
// Created by dev on 21.04.22.
//
#include <stdint.h>
#include <stdio.h>
#include "njvm.h"

int pop(int32_t* ret) {
    if (sp > 0) { // TODO: check for invalid pop over stackframe
        sp = sp-1;
        *ret = stack[sp];
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
    int32_t imm = SIGN_EXTEND(IMM(ins));
    if(dec_ins == HALT) {
        printf("Found halt instruction\n");
        return 1;
    } else if(dec_ins == PUSHC ) {
        if (push(imm) != 0) {
            return 1;
        }
    } else if(dec_ins >= ADD && dec_ins <= MOD) {
        int32_t a,b,r;
        if (pop(&b) != 0)
            return 1;
        if (pop(&a) != 0)
            return 1;
        //printf("a:%d b:%d\n",a,b);
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
        int r = scanf(" %d", &in);
        if(r != 1) {
            printf("Invalid user input, expected 1 number, got %d, aborting\n",r);
            return 1;
        }
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
        int r = scanf(" %c", &in);
        if (r != 1) {
            printf("Invalid user input, expected 1 character, got %d, aborting\n",r);
            return 1;
        }
        if (push((int32_t) in) != 0) {
            return 1;
        }
    } else if(dec_ins == WRCHR ) {
        int32_t v;
        if (pop(&v) != 0)
            return 1;
        printf("%c", v);
    } else if(dec_ins == PUSHG) {
        if (imm < static_data_area_size && imm >= 0) {
            push(static_data_area[imm]);
        } else {
            printf("Tried to PUSHG %d which is outside the SDA!\n",imm);
            return 1;
        }
    } else if(dec_ins == POPG) {
        int32_t v;
        if (pop(&v) != 0)
            return 1;
        if (imm < static_data_area_size && imm >= 0) {
            static_data_area[imm] = v;
        } else {
            printf("Tried to POPG %d which is outside the SDA!\n",imm);
            return 1;
        }
    } else if(dec_ins == ASF) {
        if (push(fp) != 0) {
            printf("No more space for pushing sp in ASF call\n");
            return 1;
        }
        fp = sp;
        sp = sp + imm;
    } else if(dec_ins == RSF) {
        sp = fp;
        int32_t v;
        if (pop(&v) != 0)
            return 1;
        fp = v;
    } else if(dec_ins == PUSHL) {
        int pos = fp + imm;
        if (pos >= sp) {
            printf("PUSHL over sp!\n");
            return 1;
        }
        if (push(stack[pos]) != 0) {
            return 1; // TODO: check fp + imm are valid
        }
    } else if(dec_ins == POPL) {
        int pos = fp + imm;
        if (pos >= sp || sp <= fp) {
            printf("POPL invalid: SP %d FP %d pos %d",sp,fp,pos);
            return 1;
        }
        int32_t v;
        if (pop(&v) != 0)
            return 1;
        stack[pos] = v;
    } else {
        printf("Found unknown op code %d\n",dec_ins);
        return 1;
    }

    return 0;
}

