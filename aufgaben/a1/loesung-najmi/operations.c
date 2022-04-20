#include <stdio.h>
#include "operations.h"
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