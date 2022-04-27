#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"
#include "execute.h"
#include "prog.h"

const int VERSION = 2;

unsigned int *program_memory;
int stack[10000];
int sp = 0;
int pc = 0;
int fp;
int *sda;
int sdaSize;

void print() {
    pc = 0;
    unsigned int ir; 
    while(1) {
        ir = program_memory[pc];
        pc = pc + 1;
        listProg(ir, pc - 1);
        if(ir >> 24 == HALT) break;
    }
}

void run() {
    pc = 0;
    unsigned int ir; 
    while(1) {
        ir = program_memory[pc];
        pc = pc + 1;
        execute(ir);
        if(ir >> 24 == HALT) break;
    } 
}

void loadProg(unsigned int *prog) {
    program_memory = malloc(10000*sizeof(unsigned int));
    pc = 0;
    while(1) {
        program_memory[pc] = prog[pc];
        if(prog[pc] >> 24 == HALT) break;
        pc++;
    }
}

void readBin(FILE *filepointer) {
    int read_len = 0;
    char c[4];
    read_len = fread(c, 1, 4, filepointer);
    if(c[0] != 'N' || c[1] != 'J' || c[2] != 'B' || c[3] != 'F') {
        exit(25);
    }

    read_len = fread(c, 1, 4, filepointer);
    if(c[0] != VERSION) {
        exit(25);
    }

    unsigned int n;
    read_len = fread(&n, 1, 4, filepointer);
    int count = SIGN_EXTEND(IMMEDIATE(n));
    program_memory = malloc(count*sizeof(unsigned int));

    read_len = fread(&n, 1, 4, filepointer);
    sdaSize = SIGN_EXTEND(IMMEDIATE(n));
    sda = malloc(sdaSize*sizeof(int));

    pc = 0;
    unsigned int ir;
    while((read_len = fread(&ir, sizeof(unsigned int), 1, filepointer)) != 0) {
        program_memory[pc] = ir;
        pc++;
    }
}

int main(int argc, char** argv) {
    FILE * filepointer;
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
            loadProg(code1); 
        } else if(strcmp("--prog2", argv[1]) == 0) {
            loadProg(code2);
        } else if(strcmp("--prog3", argv[1]) == 0) {
            loadProg(code3);
        } else if(strcmp("prog1.bin", argv[1]) == 0) {
            if((filepointer = fopen("prog1.bin", "r")) == NULL) {
                perror("Datei nicht zu oeffnen!\n");
                exit(25);
            }
            readBin(filepointer);
        } else if(strcmp("prog2.bin", argv[1]) == 0) {
            if((filepointer = fopen("prog2.bin", "r")) == NULL) {
                perror("Datei nicht zu oeffnen!\n");
                exit(25);
            }
            readBin(filepointer);
        } else {
            printf("unknown command line argument '%s', try '%s --help'\n",argv[1],argv[0]);
            return 1;
        }
    }

    printf("Ninja Virtual Machine started\n");
    print();
    printf("Ninja Virtual Machine stopped\n");
    run();

    return 0;
}