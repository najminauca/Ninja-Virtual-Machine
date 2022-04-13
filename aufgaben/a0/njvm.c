//
// Created by dev on 12.04.22.
//

#include <stdio.h>
#include <string.h>

const int VERSION = 0;

int main(int argc, char * argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1],"--help") == 0) {
            printf("usage: %s [option] [option] ...\n",argv[0]);
            printf("\t --version   show version and exit\n");
            printf("\t --help      show this help and exit\n");
            return 0;
        } else if (strcmp(argv[1],"--version") == 0) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", VERSION,__DATE__,__TIME__);
            return 0;
        } else {
            printf("unknown command line argument '%s', try '%s --help'\n",argv[1],argv[0]);
            return 1;
        }
    }

    printf("Ninja Virtual Machine started\n");

    printf("Ninja Virtual Machine stopped\n");

    return 0;
}