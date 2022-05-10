#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "execute.h"
#include "prog.h"
#include "njvm.h"

unsigned int *program_memory;
int stack[10000];
int sp = 0;
int pc = 0;
int pcSize = 0;
int fp;
int *sda;
int sdaSize;
int bp;
int runBool = 0;    //Default 0


void printStack(int i) {
    if(sp == fp) {
        printf("sp, fp  --->	");
        printNum(i);
        printf("xxxx\n");
    } else if(sp == i) {
        printf("sp      --->	");
        printNum(i);
        printf("xxxx\n");
    } else if(fp == i) {
        printf("fp      --->	");
        printNum(i);
        printf("%d\n", stack[i]);
    } else {
        printf("		");
        printNum(i);
        printf("%d\n", stack[i]);
    }
    printf(stack[i]);
}

void debugRun() {
    unsigned int ir = program_memory[pc];
    listProg(ir, pc - 1);
    while(1) {
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");

        char c[20] = "";
        scanf("%s", c);

        if(strcmp(c, "inspect") == 0) {
            printf("DEBUG [inspect]: stack, data?\n");
            scanf("%s", c);

            if(strcmp(c, "stack") == 0) {
                int i = sp;
                //printf("sp      --->	0010:	xxxx")
                while(i >= 0) {
                    printStack(i);
                    i--;
                }
                printf("		--- bottom of stack ---\n");
                listProg(ir, pc - 1);
            } else if(strcmp(c, "data") == 0) {
                for(int i = 0; i < sdaSize; i++) {
                    if(i < 10) {
                        printf("data[000%d]:	%d\n", i, sda[i]);
                    } else if(i < 100) {
                        printf("data[0%d]:	%d\n", i, sda[i]);
                    } else {
                        printf("data[%d]:	%d\n", i, sda[i]);
                    }
                    printf("	--- end of data ---\n");
                    listProg(ir, pc - 1);
                }
            }
            if(strcmp(c, "list") == 0) {
                int temp = pc;
                print();
                pc = temp;
            } else if(strcmp(c, "breakpoint") == 0) {
                if(bp == -1) {
                    printf("DEBUG [breakpoint]: cleared\n");
                } else {
                    printf("DEBUG [breakpoint]: set at %d\n", bp);
                }
                printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");

                if(scanf("%d", &bp) == 1) {
                    if(bp == -1) {
                        printf("DEBUG [breakpoint]: now cleared\n");
                    } else {
                        printf("DEBUG [breakpoint]: now set at %d\n", bp);
                    }
                }
                listProg(ir, pc - 1);
            } else if(strcmp(c, "step" == 0)) {
                break;
            } else if(strcmp(c, "run") == 0) {
                int temp = pc;
                printf("Ninja Virtual Machine started\n");
                print();
                run();
                printf("Ninja Virtual Machine stopped\n");
                pc = temp;
                break;
            } else if(strcmp(c, "quit") == 0) {
                break;
            } else {
                continue
            }
        }
    }
}

int main(int argc, char** argv) {
}