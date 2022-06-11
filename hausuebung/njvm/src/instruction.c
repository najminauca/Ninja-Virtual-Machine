//
// Created by Aron Heinecke on 14.05.22.
//
#include <stdio.h>
#include <stdint.h>
#include "njvm.h"
#include "exec.h"
#include "bigint.h"

int pushc(int32_t imm) {
    return pushObjRef(createIntObj(imm));
}

int add() {
    ObjRef ao, bo;
    if (popObjRef(&bo) != 0 || popObjRef(&ao) != 0)
        return 1;
    bip.op1 = ao;
    bip.op2 = bo;
    bigAdd();
    return pushObjRef(bip.res);
}

int sub() {
    ObjRef ao, bo;
    if (popObjRef(&bo) != 0 || popObjRef(&ao) != 0)
        return 1;
    bip.op1 = ao;
    bip.op2 = bo;
    bigSub();
    return pushObjRef(bip.res);
}

int mul() {
    ObjRef ao, bo;
    if (popObjRef(&bo) != 0 || popObjRef(&ao) != 0)
        return 1;
    bip.op1 = ao;
    bip.op2 = bo;
    bigMul();
    return pushObjRef(bip.res);
}

int c_div() {
    ObjRef ao, bo;
    if (popObjRef(&bo) != 0 || popObjRef(&ao) != 0)
        return 1;
    bip.op1 = ao;
    bip.op2 = bo;
    bigDiv();
    return pushObjRef(bip.res);
}

int mod() {
    ObjRef ao, bo;
    if (popObjRef(&bo) != 0 || popObjRef(&ao) != 0)
        return 1;
    bip.op1 = ao;
    bip.op2 = bo;
    bigDiv();
    return pushObjRef(bip.rem);
}

int rdint() {
    int32_t in = 0;
    int r = scanf(" %d", &in);
    if (r != 1) {
        printf("ERROR: Invalid user input, expected 1 number, got %d, aborting\n", r);
        return 1;
    }
    return pushObjRef(createIntObj(in));
}

int wrint() {
    ObjRef vo;
    if (popObjRef(&vo) != 0)
        return 1;
    bip.op1 = vo;
    bigPrint(stdout);
    return 0;
}

int rdchr() {
    char in = 0;
    int r = scanf(" %c", &in);
    if (r != 1) {
        printf("ERROR: Invalid user input, expected 1 character, got %d, aborting\n", r);
        return 1;
    }
    return pushObjRef(createIntObj((int32_t) in));
}

int wrchr() {
    ObjRef vo;
    if (popObjRef(&vo) != 0)
        return 1;
    bip.op1 = vo;
    int v = bigToInt();
    printf("%c", v);
    return 0;
}

int pushg(int32_t imm) {
    if (imm < static_data_area_size && imm >= 0) {
        pushObjRef(static_data_area[imm]);
        return 0;
    } else {
        printf("Error: PUSHG to %d which is outside the SDA!\n", imm);
        return 1;
    }
}

int popg(int32_t imm) {
    ObjRef v;
    if (popObjRef(&v) != 0)
        return 1;
    if (imm < static_data_area_size && imm >= 0) {
        static_data_area[imm] = v;
        return 0;
    } else {
        printf("Error: POPG to %d which is outside the SDA!\n", imm);
        return 1;
    }
}

int asf(int32_t imm) {
    if (pushInt(fp) != 0) {
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
    if (popInt(&v) != 0)
        return 1;
    fp = v;
    return 0;
}

int pushl(int32_t imm) {
    int pos = fp + imm;
    if (pos >= sp || pos < 0) {
        printf("Error: PUSHL over sp!\n");
        return 1;
    }
    if (!stack[pos].isObjRef) {
        printf("Error: PUSHL on int, wanted objref!\n");
        return 1;
    }
    return pushObjRef(stack[pos].u.objRef);
}

int popl(int32_t imm) {
    int pos = fp + imm;
    if (pos >= sp || sp <= fp) {
        printf("Error: POPL invalid SP %d FP %d pos %d\n", sp, fp, pos);
        return 1;
    }
    ObjRef v;
    if (popObjRef(&v) != 0) {
        return 1;
    }
    stack[pos].isObjRef = true;
    stack[pos].u.objRef = v;
    return 0;
}

int eq() {
    ObjRef a, b;
    if (popObjRef(&b) != 0 || popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    bip.op2 = b;
    int val = 0;
    if (bigCmp() == 0) {
        val = 1;
    }
    return pushObjRef(createIntObj(val));
}

int ne() {
    ObjRef a, b;
    if (popObjRef(&b) != 0 || popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    bip.op2 = b;
    int val = 0;
    if (bigCmp() != 0) { // !=
        val = 1;
    }
    return pushObjRef(createIntObj(val));
}

int lt() {
    ObjRef a, b;
    if (popObjRef(&b) != 0 || popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    bip.op2 = b;
    int val = 0;
    if (bigCmp() < 0) { // <
        val = 1;
    }
    return pushObjRef(createIntObj(val));
}

int le() {
    ObjRef a, b;
    if (popObjRef(&b) != 0 || popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    bip.op2 = b;
    int val = 0;
    if (bigCmp() < 1) { // <=
        val = 1;
    }
    return pushObjRef(createIntObj(val));
}

int gt() {
    ObjRef a, b;
    if (popObjRef(&b) != 0 || popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    bip.op2 = b;
    int val = 0;
    if (bigCmp() >= 1) { // >
        val = 1;
    }
    return pushObjRef(createIntObj(val));
}

int ge() {
    ObjRef a, b;
    if (popObjRef(&b) != 0 || popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    bip.op2 = b;
    int val = 0;
    if (bigCmp() > -1) { // >=
        val = 1;
    }
    return pushObjRef(createIntObj(val));
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
    ObjRef a;
    if (popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    // returns whether a is <, =, > 0
    if (bigSgn() == 0) {
        if (imm > programm_size || imm < 0) {
            printf("Error: BRF to %d out of range\n", imm);
            return 1;
        }
        pc = imm;
    }
    return 0;
}

int brt(int32_t imm) {
    ObjRef a;
    if (popObjRef(&a) != 0)
        return 1;
    bip.op1 = a;
    if (bigSgn() != 0) {
        if (imm > programm_size || imm < 0) {
            printf("Error: BRT to %d out of range\n", imm);
            return 1;
        }
        pc = imm;
    }
    return 0;
}

int call(int32_t imm) {
    if (pushInt(pc) != 0) {
        return 1;
    }
    pc = imm;
    return 0;
}

int ret() {
    return popInt(&pc);
}

int drop(int32_t imm) {
    sp = sp - imm;
    if (sp < 0) {
        printf("Error: drop to %d out of range\n", sp);
        return 1;
    }
    return 0;
}

int pushr() {
    return pushObjRef(rvr);
}

int popr() {
    return popObjRef(&rvr);
}

int dup() {
    if (!stack[sp - 1].isObjRef) {
        printf("Error: can't dup on int, expected objref! stackpointer %d\n", sp);
        return 1;
    }
    return pushObjRef(stack[sp - 1].u.objRef);
}