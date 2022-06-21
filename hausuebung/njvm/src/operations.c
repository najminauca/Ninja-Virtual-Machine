#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "njvm.h"
#include "bigint.h"

int popInt(void) {
    if(!stack[sp - 1].isObjRef) {
        sp--;
        return stack[sp].u.number;
    }
}

ObjRef popObjRef(void) {
    if(stack[sp - 1].isObjRef) {
        sp--;
        return stack[sp].u.objRef;
    }
}

void pushObjRef(ObjRef o) {
    if(sp < MAX) {
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = o;
        sp++;
    }
}

void pushInt(int i) {
    if(sp < MAX) {
        stack[sp].isObjRef = false;
        stack[sp].u.number = i;
        sp++;
    }
}

void pushc(int immediate) {
    bigFromInt(immediate);
    pushObjRef(bip.res);
}

void add(void) {
    if(sp > 1){
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        bigAdd();
        pushObjRef(bip.res);
    }
}

void sub(void) {
    if(sp > 1){
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        bigSub();
        pushObjRef(bip.res);
    }
}

void mul(void) {
    if(sp > 1){
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        bigMul();
        pushObjRef(bip.res);
    }
}

void divnjvm(void) {
    if(sp > 1 && *(int *)stack[sp - 1].u.objRef->data != 0){
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        bigDiv();
        pushObjRef(bip.res);
    }
}

void mod(void) {
    if(sp > 1){
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        bigDiv();
        pushObjRef(bip.rem);
    }
}

void rdint(void) {
    bigRead(stdin);
    pushObjRef(bip.res);
}

void wrint(void) {
    if(sp > 0) {
        bip.op1 = popObjRef();
        bigPrint(stdout);
    }
}

void rdchr(void) {
    char read;
    scanf("%c", &read);
    pushc((int)read);
}

void wrchr(void) {
    if(sp > 0) {
        bip.op1 = popObjRef();
        int i = bigToInt();
        printf("%c", i);
    }
}

void pushg(int i) {
    if(i < sdaSize) {
        pushObjRef(sda[i]);
    }
}

void popg(int i) {
    if(i < sdaSize) {
        sda[i] = popObjRef();
    }
}

void asf(int size) {
    pushInt(fp);
    fp = sp;
    sp = sp + size;
    /*int i = 0;
    while(i < size) {
        stack[sp].isObjRef = false;
        sp++;
        i++;
    }*/
    fSize = size;
}

void rsf(void) {
    if(fp != 0) {
        sp = fp;
        fp = popInt();
        fSize = sp - fp;
    }
}

void pushl(int i) {
    int pos = fp + i;
    if(pos < fp + fSize) {
        pushObjRef(stack[pos].u.objRef);
    }
}

void popl(int i) {
    int pos = fp + i;
    if(sp > fp && pos < fp + fSize) {
        stack[pos].isObjRef = true;
        stack[pos].u.objRef = popObjRef();
    }
}

void eq(void) {
    if(sp > 1) {
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        if(bigCmp() == 0) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void ne(void) {
    if(sp > 1) {
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        if(bigCmp() != 0) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void lt(void) {
    if(sp > 1) {
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        if(bigCmp() < 0) { //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void le(void) {
    if(sp > 1) {
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        if(bigCmp() < 1) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void gt(void) {
    if(sp > 1) {
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        if(bigCmp() > 0) { //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void ge(void) { 
    if(sp > 1) {
        bip.op2 = popObjRef();
        bip.op1 = popObjRef();
        if(bigCmp() > -1) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }  
}

void jmp(int target) {
    pc = target;
}

void brf(int target) {
    bip.op1 = popObjRef();
    if(bigSgn() == 0) {    //False
        pc = target;
    }
}

void brt(int target) {
    bip.op1 = popObjRef();
    if(bigSgn() != 0) {    //True
        pc = target;
    }
}

void call(int target) {
    pushInt(pc);
    pc = target;
}

void ret(void) {
    pc = popInt();
}

void drop(int n) {
    if(sp - n >= 0) {
        sp = sp - n;
    }
}

void pushr(void) {
    if(sp > 1) {
        pushObjRef(returnRegister);
    }
}

void popr(void) {
    returnRegister = popObjRef();
}

void dup(void) {
    if(sp > 0) {
        pushObjRef(stack[sp - 1].u.objRef);
    }
}