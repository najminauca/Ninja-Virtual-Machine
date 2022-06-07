#include <stdio.h>
#include <stdlib.h>
#include "njvm.h"

int pop(void) {
    sp--;
    return *(int *)stack[sp].u.objRef->data;
}

void push(int i) {
    if(sp < MAX) {
        ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
        obj->size = sizeof(int);
        *(int *)obj->data = i;
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = obj;
        sp++;
    }
}

void pushc(int immediate) {
    push(immediate);
}

void add(void) {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a + b);
    }
}

void sub(void) {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a - b);
    }
}

void mul(void) {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a * b);
    }
}

void divnjvm(void) {
    if(sp > 1 && *(int *)stack[sp - 1].u.objRef->data != 0){
        int b = pop();
        int a = pop();
        pushc(a / b);
    }
}

void mod(void) {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a % b);
    }
}

void rdint(void) {
    int read;
    scanf("%d", &read);
    pushc(read);
}

void wrint(void) {
    if(sp > 0) {
        printf("%d", pop());
    }
}

void rdchr(void) {
    char read;
    scanf("%c", &read);
    pushc(read);
}

void wrchr(void) {
    if(sp > 0) {
        printf("%c", pop());
    }
}

void pushg(int i) {
    if(i < sdaSize) {
        pushc(*(int *)sda[i]->data);
    }
}

void popg(int i) {
    if(i < sdaSize) {
        ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
        obj->size = sizeof(int);
        *(int *)obj->data = pop();
        sda[i] = obj;
    }
}

void asf(int size) {
    pushc(fp);
    fp = sp;
    int i = 0;
    while(i < size) {
        pushc(0);
        i++;
    }
    fSize = size;
}

void rsf(void) {
    if(fp != 0) {
        sp = fp;
        fp = pop();
        fSize = sp - fp;
    }
}

void pushl(int i) {
    int pos = fp + i;
    if(pos < fp + fSize) {
        pushc(*(int *)stack[pos].u.objRef->data);
    }
}

void popl(int i) {
    int pos = fp + i;
    if(sp > fp && pos < fp + fSize) {
        ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
        obj->size = sizeof(int);
        *(int *)obj->data = pop();
        stack[pos].isObjRef = true;
        stack[pos].u.objRef = obj;
    }
}

void eq(void) {
    if(sp > 1) {
        int b = pop();
        int a = pop();
        if(a == b) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void ne(void) {
    if(sp > 1) {
        int b = pop();
        int a = pop();
        if(a != b) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void lt(void) {
    if(sp > 1) {
        int b = pop();
        int a = pop();
        if(a < b) { //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void le(void) {
    if(sp > 1) {
        int b = pop();
        int a = pop();
        if(a <= b) {    //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void gt(void) {
    if(sp > 1) {
        int b = pop();
        int a = pop();
        if(a > b) { //True
            pushc(1);
        }
        else {  //False
            pushc(0);
        }
    }
}

void ge(void) { 
    if(sp > 1) {
        int b = pop();
        int a = pop();
        if(a >= b) {    //True
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
    if(pop() == 0) {    //False
        pc = target;
    }
}

void brt(int target) {
    if(pop() == 1) {    //True
        pc = target;
    }
}

void call(int target) {
    pushc(pc);
    pc = target;
}

void ret(void) {
    pc = pop();
}

void drop(int n) {
    if(sp - n >= 0) {
        sp = sp - n;
    }
}

void pushr(void) {
    if(sp > 1) {
        pushc(*(int *)returnRegister->data);
    }
}

void popr(void) {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    *(int *)obj->data = pop();
    returnRegister = obj;
    sp--;
}

void dup(void) {
    if(sp > 0) {
        pushc(*(int*)stack[sp - 1].u.objRef->data);
    }
}