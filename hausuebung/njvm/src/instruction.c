//
// Created by Aron Heinecke on 14.05.22.
//
#include <stdio.h>
#include <stdint.h>
#include "njvm.h"
#include "exec.h"

int add() {
    int32_t a, b, r;
    if (pop(&b) != 0)
        return 1;
    if (pop(&a) != 0)
        return 1;
    return push(a + b);
}

int sub() {
    int32_t a, b, r;
    if (pop(&b) != 0)
        return 1;
    if (pop(&a) != 0)
        return 1;
    return push(a - b);
}

int mul() {
    int32_t a, b;
    if (pop(&b) != 0)
        return 1;
    if (pop(&a) != 0)
        return 1;
    return push(a * b);
}

int div() {
    int32_t a, b;
    if (pop(&b) != 0)
        return 1;
    if (pop(&a) != 0)
        return 1;
    return push(a / b);
}

int mod() {
    int32_t a, b;
    if (pop(&b) != 0)
        return 1;
    if (pop(&a) != 0)
        return 1;
    return push(a % b);
}

int rdint() {
    int32_t in = 0;
    int r = scanf(" %d", &in);
    if (r != 1) {
        printf("ERROR: Invalid user input, expected 1 number, got %d, aborting\n", r);
        return 1;
    }
    return push(in);
}

int wrint() {
    int32_t v;
    if (pop(&v) != 0)
        return 1;
    printf("%d", v);
    return 0;
}

int rdchr() {
    char in = 0;
    int r = scanf(" %c", &in);
    if (r != 1) {
        printf("ERROR: Invalid user input, expected 1 character, got %d, aborting\n", r);
        return 1;
    }
    return push((int32_t) in);
}

int wrchr() {
    int32_t v;
    if (pop(&v) != 0)
        return 1;
    printf("%c", v);
    return 0;
}

int pushg(int32_t imm) {
    if (imm < static_data_area_size && imm >= 0) {
        push(static_data_area[imm]);
    } else {
        printf("Error: PUSHG to %d which is outside the SDA!\n", imm);
        return 1;
    }
}

int popg(int32_t imm) {
    int32_t v;
    if (pop(&v) != 0)
        return 1;
    if (imm < static_data_area_size && imm >= 0) {
        static_data_area[imm] = v;
    } else {
        printf("Error: POPG to %d which is outside the SDA!\n", imm);
        return 1;
    }
}

int asf(int32_t imm) {
    if (push(fp) != 0) {
        printf("Error: No more space for pushing sp in ASF call\n");
        return 1;
    }
    fp = sp;
    sp = sp + imm;
    return 0;
}

int rsf() {
    sp = fp;
    int32_t v;
    if (pop(&v) != 0)
        return 1;
    fp = v;
    return 0;
}

int pushl(int32_t imm) {
    int pos = fp + imm;
    if (pos >= sp) {
        printf("Error: PUSHL over sp!\n");
        return 1;
    }
    // TODO: check fp + imm are valid
    return push(stack[pos]);
}

int popl(int32_t imm) {
    int pos = fp + imm;
    if (pos >= sp || sp <= fp) {
        printf("Error: POPL invalid SP %d FP %d pos %d", sp, fp, pos);
        return 1;
    }
    int32_t v;
    if (pop(&v) != 0)
        return 1;
    stack[pos] = v;
    return 0;
}

int eq() {
    int32_t a, b;
    if (pop(&a) != 0)
        return 1;
    if (pop(&b) != 0)
        return 1;
    return push(a == b);
}

int ne() {
    int32_t a, b;
    if (pop(&a) != 0)
        return 1;
    if (pop(&b) != 0)
        return 1;
    return push(a != b);
}

int lt() {
    int32_t a, b;
    if (pop(&a) != 0)
        return 1;
    if (pop(&b) != 0)
        return 1;
    return push(a < b);
}

int le() {
    int32_t a, b;
    if (pop(&a) != 0)
        return 1;
    if (pop(&b) != 0)
        return 1;
    return push(a <= b);
}

int gt() {
    int32_t a, b;
    if (pop(&a) != 0)
        return 1;
    if (pop(&b) != 0)
        return 1;
    return push(a > b);
}

int ge() {
    int32_t a, b;
    if (pop(&a) != 0)
        return 1;
    if (pop(&b) != 0)
        return 1;
    return push(a >= b);
}

int jmp(int32_t imm) {
    if (imm >= programm_size || imm < 0) {
        printf("Error: JMP to %d out of range\n", imm);
        return 1;
    }
    pc = imm;
    return 0;
}

int brf(int32_t imm) {
    int32_t a;
    if (pop(&a) != 0)
        return 1;
    if (a == 0) {
        if (imm > programm_size || imm < 0) {
            printf("Error: BRF to %d out of range\n", imm);
            return 1;
        }
        pc = imm;
    }
    return 0;
}

int brt(int32_t imm) {
    int32_t a;
    if (pop(&a) != 0)
        return 1;
    if (a == 1) {
        if (imm > programm_size || imm < 0) {
            printf("Error: BRT to %d out of range\n", imm);
            return 1;
        }
        pc = imm;
    }
    return 0;
}