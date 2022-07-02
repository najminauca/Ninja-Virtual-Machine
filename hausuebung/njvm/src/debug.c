#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "execute.h"
#include "njvm.h"
#include "bigint.h"

int bp = -1;

void printStack(int i) {
    if(sp == fp) {
        printf("sp, fp  --->	");
        printNum(i);
        printf("(xxxxxx) xxxxxx\n");
    } else if(sp == i) {
        printf("sp      --->	");
        printNum(i);
        printf("(xxxxxx) xxxxxx\n");
    } else if(fp == i) {
        printf("fp      --->	");
        printNum(i);
        if(stack[i].isObjRef) {
            printf("(objref) %p\n", (void *)stack[i].u.objRef);
        } else {
            printf("(number) %d\n", (int)stack[i].u.number);
        }
        
    } else {
        printf("		");
        printNum(i);
        if(stack[i].isObjRef) {
            printf("(objref) %p\n", (void *)stack[i].u.objRef);
        } else {
            printf("(number) %d\n", (int)stack[i].u.number);
        }
    }
}

void debugRun(unsigned int ir) {
    while(runBool != 1) {
        listProg(ir, pc - 1);
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");

        char c[20] = "";
        scanf("%s", c);

        if(strcmp(c, "inspect") == 0) {
            printf("DEBUG [inspect]: stack, data, object?\n");
            scanf("%s", c);

            if(strcmp(c, "stack") == 0) {
                int i = sp;
                while(i >= 0) {
                    printStack(i);
                    i--;
                }
                printf("		--- bottom of stack ---\n");
            } else if(strcmp(c, "data") == 0) {
                for(int i = 0; i < sdaSize; i++) {
                    if(i < 10) {
                        printf("data[000%d]:	%d\n", i, *(int *)sda[i]->data);
                    } else if(i < 100) {
                        printf("data[0%d]:	%d\n", i, *(int *)sda[i]->data);
                    } else {
                        printf("data[%d]:	%d\n", i, *(int *)sda[i]->data);
                    }
                }
                printf("	--- end of data ---\n");
            } else if(strcmp(c, "object") == 0) {
                printf("object position in stack?\n");
                int i;
                scanf("%d", &i);
                if(i >= 0 && stack[i].isObjRef) {
                    if(stack[i].u.objRef == NULL) {
                        printf("(objref) nil\n");
                        printf("	--- end of object ---\n");
                    }
                    else if(!IS_PRIM(stack[i].u.objRef)) {
                    printf("<compound object>\n");
                        if(stack[i].u.objRef != NULL) {
                            int size = GET_SIZE(stack[i].u.objRef);
                            for(int j = 0; j < size; j++) {
                                printf("field ");
                                printNum(j);
                                printf("(objref) %p\n", (void*) GET_REFS(stack[i].u.objRef)[j]);
                            }
                            printf("	--- end of object ---\n");
                        } else {
                            printf("field ");
                            printNum(0);
                            printf("(objref) %p\n", (void*) GET_REFS(stack[i].u.objRef));
                            printf("	--- end of object ---\n");
                        }
                    
                    } else if(IS_PRIM(stack[i].u.objRef)) {
                        printf("<primitive object>\n");
                        printf("(value)         ");
                        bip.op1 = stack[i].u.objRef;
                        bigPrint(stdout);
                        printf("\n");
                        printf("	--- end of object ---\n");
                    }
                }
            }
        }
        else if(strcmp(c, "list") == 0) {
                int temp = pc;
                print();
                printf("	--- end of code ---\n");
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
        } else if(strcmp(c, "step") == 0) {
            execute(ir);
            break;
        } else if(strcmp(c, "run") == 0) {
            runBool = 1;
        } else if(strcmp(c, "quit") == 0) {
            quit = 1;
            break;
        } else {
            continue;
        }
    }

    if(runBool == 1) {
        execute(ir);
    }

    if(pc == bp) runBool = 0;
}