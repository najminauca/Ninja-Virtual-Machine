#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "execute.h"
#include "prog.h"

unsigned int programm_speicher[1000];
int stack[1000];
int sp = 0;
int pc = 0;

const int VERSION = 1;

int main(int argc, char** argv) {

    printf("Ninja Virtual Machine started\n");

    if (argc > 1) {
        if (strcmp(argv[1],"--help") == 0) {
            printf("usage: %s [option] [option] ...\n",argv[0]);
            printf("\t --version   show version and exit\n");
            printf("\t --help      show this help and exit\n");
            return 0;
        } else if (strcmp(argv[1],"--version") == 0) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", VERSION,__DATE__,__TIME__);
            return 0;
        } else if(strcmp("--prog1", argv[1]) == 0) {
            while(1) {
                unsigned int ir = code1[pc];
                pc = pc + 1;
                listProg(ir, pc - 1);
                if(ir >> 24 == 0) break;
            }
            pc = 0;
            while(1) {
                unsigned int ir = code1[pc];
                pc = pc + 1;
                execute(ir);
                if(ir >> 24 == 0) break;
            }  
        } else if(strcmp("--prog2", argv[1]) == 0) {
            while(1) {
                unsigned int ir = code2[pc];
                pc = pc + 1;
                listProg(ir, pc - 1);

                if(ir >> 24 == 0) break;
            }
            pc = 0;
            while(1) {
                unsigned int ir = code2[pc];
                pc = pc + 1;
                execute(ir);
                if(ir >> 24 == 0) break;
            }
        } else if(strcmp("--prog3", argv[1]) == 0) {
            while(1) {
                unsigned int ir = code3[pc];
                pc = pc + 1;
                listProg(ir, pc - 1);
                if(ir >> 24 == 0) break;
            }
            pc = 0;
            while(1) {
                unsigned int ir = code3[pc];
                pc = pc + 1;
                execute(ir);
                if(ir >> 24 == 0) break;
            }
        } else {
            printf("unknown command line argument '%s', try '%s --help'\n",argv[1],argv[0]);
            return 1;
        }
    }

    printf("Ninja Virtual Machine stopped\n");

    return 0;
}