//
// Created by dev on 20.04.22.
//

//
// Created by dev on 12.04.22.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "njvm.h"

const int VERSION = 0;

void load_program(const int32_t source[]) {
    pc = 0;
    while(1) {
        programm_speicher[pc] = source[pc];
        if (source[pc] >> 24 == 0)
            break;
        pc = pc + 1;
    }
    printf("Loaded %d instructions",pc);
    pc = 0;
}

int pop(int32_t* ret) {
    if (sp > 0) {
        sp = sp -1;
        *ret = stack[sp + 1];
        return 0;
    } else {
        printf("Tried to pop on stack pointer %d",sp);
        return 1;
    }
}

int push(int32_t val) {
    if (sp > STACK_LIMIT) {
        printf("Tried to push over stack limit");
        return 1;
    } else {
        sp = sp + 1;
        stack[sp] = val;
        return 0;
    }
}

int execute(uint32_t ins) {
    uint32_t dec_ins = ins >> 24;
    if(dec_ins == HALT) {
        printf("Found halt instruction");
        return 1;
    } else if(dec_ins == PUSHC ) {
        int32_t imm = SIGN_EXTEND(ins & 0x00FFFFFF);

    } else if(dec_ins == ADD ) {

    } else if(dec_ins == SUB ) {

    } else if(dec_ins == MUL ) {

    } else if(dec_ins == DIV ) {

    } else if(dec_ins == MOD ) {
    } else if(dec_ins == RDINT ) {
    } else if(dec_ins == WRINT ) {
    } else if(dec_ins == RDCHR ) {
    } else if(dec_ins == WRCHR ) {0

    return 0;
}

void run() {
    while(1) {
        uint32_t ins = programm_speicher[pc];
        pc = pc + 1;
        if(execute(ins)) {
            break;
        }
    }
}

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1],"--help") == 0) {
            printf("usage: %s [option] [option] ...\n",argv[0]);
            printf("\t --version   show version and exit\n");
            printf("\t --help      show this help and exit\n");
            return 0;
        } else if (strcmp(argv[1],"--version") == 0) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", VERSION, __DATE__, __TIME__);
            return 0;
        } else if (strcmp(argv[1],"--prog1") == 0) {
                printf("Loading program 1\n");
                load_program(prog_1);
        } else if (strcmp(argv[1],"--prog2") == 0) {
            printf("Loading program 2\n");
            load_program(prog_2);
        } else if (strcmp(argv[1],"--prog3") == 0) {
            printf("Loading program 3\n");
            load_program(prog_3);
        } else {
            printf("unknown command line argument '%s', try '%s --help'\n",argv[1],argv[0]);
            return 1;
        }
    }

    printf("Ninja Virtual Machine started\n");

    printf("Ninja Virtual Machine stopped\n");

    return 0;
}

