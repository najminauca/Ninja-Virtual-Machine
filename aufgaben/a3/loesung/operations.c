#include <stdio.h>
#include "njvm.h"

int pop() {
    sp--;
    return stack[sp];
}

void push(int i) {
    if(sp < MAX) {
        stack[sp] = i;
        sp++;
    }
}

void pushc(int immediate) {
    push(immediate);
}

void add() {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a + b);
    }
}

void sub() {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a - b);
    }
}

void mul() {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a * b);
    }
}

void divnjvm() {
    if(sp > 1 && stack[sp - 1] != 0){
        int b = pop();
        int a = pop();
        pushc(a / b);
    }
}

void mod() {
    if(sp > 1){
        int b = pop();
        int a = pop();
        pushc(a % b);
    }
}

void rdint() {
    int read;
    scanf("%d", &read);
    pushc(read);
}

void wrint() {
    if(sp > 0) {
        printf("%d", pop());
    }
}

void rdchr() {
    char read;
    scanf("%c", &read);
    pushc(read);
}

void wrchr() {
    if(sp > 0) {
        printf("%c", pop());
    }
}

void pushg(int i) {
    if(i < sdaSize) {
        pushc(sda[i]);
    }
}

void popg(int i) {
    if(i < sdaSize) {
        sda[i] = pop();
    }
}

void asf(int size) {
    pushc(fp);
    fp = sp;
    sp = sp + size;
    fSize = size;
}

void rsf() {
    if(fp != 0) {
        while(sp != fp) {
            sp--;
        }
        fp = pop();
        fSize = sp - fp;
    }
}

void pushl(int i) {
    int pos = fp + i;
    if(pos < fp + fSize) {
        pushc(stack[pos]);
    }
}

void popl(int i) {
    int pos = fp + i;
    if(sp > fp && pos < fp + fSize) {
        stack[pos] = pop();
    }
}

void eq() {
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

void ne() {
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

void lt() {
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

void le() {
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

void gt() {
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

void ge() { 
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