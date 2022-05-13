#include <stdio.h>
#include "njvm.h"

void pushc(int immediate) {
    stack[sp] = immediate;
    sp++;
}
void add() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
        sp--;
    }
}
void sub() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
        sp--;
    }
}
void mul() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] * stack[sp - 1];
        sp--;
    }
}
void divnjvm() {
    if(sp > 1 && stack[sp - 1] != 0){
        stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
        sp--;
    }
}
void mod() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] % stack[sp - 1];
        sp--;
    }
}
void rdint() {
    int read;
    scanf("%d", &read);
    stack[sp] = read;
    sp++;
}
void wrint() {
    if(sp > 0) {
        printf("%d", stack[sp - 1]);
        sp--;
    }
}
void rdchr() {
    char read;
    scanf("%c", &read);
    stack[sp] = read;
    sp++;
}
void wrchr() {
    if(sp > 0) {
        printf("%c", stack[sp - 1]);
        sp--;
    }
}

void pushg(int i) {
    if(i < sdaSize) {
        stack[sp] = sda[i];
        sp++;
    }
}

void popg(int i) {
    if(i < sdaSize) {
        sda[i] = stack[sp - 1];
        sp--;
    }
}

void asf(int size) {
    pushc(fp);
    fp = sp;
    sp = sp + size;
}

void rsf() {
    if(fp != 0) {
        sp = fp;
        fp = stack[fp - 1];
        sp--;
    }
}

void pushl(int i) {
    int pos = fp + i;
    if(pos < sp) {
        pushc(stack[pos]);
    }
}

void popl(int i) {
    int pos = fp + i;
    if(sp > fp && pos < sp) {
        stack[pos] = stack[sp - 1];
        sp--;
    }
}