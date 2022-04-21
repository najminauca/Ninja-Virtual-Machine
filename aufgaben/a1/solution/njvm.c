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
#include "exec.h"
#include "programme.h"
#include "printer.h"

const int VERSION = 0;

uint32_t programm_speicher[PROGRAM_LIMIT];
int32_t stack[STACK_LIMIT];
int sp = 0;
int pc = 0;

void load_program(const int32_t source[]) {
    pc = 0;
    while(1) {
        programm_speicher[pc] = source[pc];
        if (source[pc] >> 24 == 0)
            break;
        pc = pc + 1;
    }
    printf("Loaded %d instructions\n",pc);
    pc = 0;
}

void run() {
    int count = 0;
    while(1) {
        uint32_t ins = programm_speicher[pc];
        pc = pc + 1;
        count = count + 1;
        if(execute(ins)) {
            break;
        }
    }
    printf("Finished after %d cycles\n",count);
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

    printProgram();
    printf("Ninja Virtual Machine started\n");
    run();
    printf("Ninja Virtual Machine stopped\n");

    return 0;
}

