#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"
#include "operations.h"
#include "execute.h"
#include "prog.h"

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
            listProg(code1);
            execute(code1);
        } else if(strcmp("--prog2", argv[1]) == 0) {
            listProg(code2);
            execute(code2);
        } else if(strcmp("--prog3", argv[1]) == 0) {
            listProg(code3);
            execute(code3);
        } else {
            printf("unknown command line argument '%s', try '%s --help'\n",argv[1],argv[0]);
            return 1;
        }
    }

    printf("Ninja Virtual Machine stopped\n");

    return 0;
}