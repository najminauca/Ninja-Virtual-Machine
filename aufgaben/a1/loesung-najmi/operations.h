#define HALT 0

#define PUSHC 1
void pushc(int immediate) {
    stack[sp] = immediate;
    sp++;
}

#define ADD 2
void add() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
        sp--;
    }
}

#define SUB 3
void sub() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
        sp--;
    }
}

#define MUL 4
void mul() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] * stack[sp - 1];
        sp--;
    }
}

#define DIV 5
void divnjvm() {
    if(sp > 1 && stack[sp - 1] != 0){
        stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
        sp--;
    }
}

#define MOD 6
void mod() {
    if(sp > 1){
        stack[sp - 2] = stack[sp - 2] % stack[sp - 1];
        sp--;
    }
}

#define RDINT 7
void rdint() {
    int read;
    scanf("%d", &read);
    stack[sp] = read;
    sp++;
}

#define WRINT 8
void wrint() {
    if(sp > 0) {
        printf("%d", stack[sp - 1]);
        stack[sp - 1] = 0;
        sp--;
    }
}

#define RDCHR 9
void rdchr() {
    char read;
    scanf("%c", &read);
    stack[sp] = read;
    sp++;
}

#define WRCHR 10
void wrchr() {
    if(sp > 0) {
        printf("%c", stack[sp - 1]);
        stack[sp - 1] = 0;
        sp--;
    }
}