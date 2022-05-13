//
// Created by dev on 20.04.22.
//

//
// Created by dev on 12.04.22.
//

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "njvm.h"
#include "exec.h"
#include "programme.h"
#include "printer.h"

const int VERSION = 0;

uint32_t *programm_speicher;
int32_t stack[STACK_LIMIT];
int sp = 0;
int pc = 0;

void load_program(const char* path) {
    FILE * fp;
    size_t read_ojects;
    fp = fopen(path,"r");
    if (fp == NULL) {
        perror("Unable to load program from file.");
        exit(1);
    }
    int header_count = 4;
    uint32_t headers[header_count];
    read_ojects = fread(headers,sizeof(uint32_t),header_count,fp);
    if (read_ojects != header_count) {
        printf("ERROR: Could not read a full header for the programm.");
        exit(1);
    }
    printf("Format %c\n",headers[0]);
    printf("Version %d\n",headers[1]);
    printf("Number of instructions %d\n",headers[2]);
    printf("Static variables %d\n",headers[3]);

    programm_speicher = malloc(headers[2]);
    read_ojects = fread(programm_speicher,sizeof(uint32_t),headers[2],fp);
    if (read_ojects != headers[2]) {
        printf("ERROR: Mismatch of instruction size header and file length!");
        exit(1);
    }

//    pc = 0;
//    while(1) {
//        programm_speicher[pc] = source[pc];
//        if (source[pc] >> 24 == 0)
//            break;
//        pc = pc + 1;
//    }
//    printf("Loaded %d instructions\n",pc);
//    pc = 0;
}

void run() {
    int count = 0;
    sp = 0;
    pc = 0;
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
            printf("usage: %s [options] <code file>\n",argv[0]);
            printf("\t --version   show version and exit\n");
            printf("\t --help      show this help and exit\n");
            return 0;
        } else if (strcmp(argv[1],"--version") == 0) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", VERSION, __DATE__, __TIME__);
            return 0;
        } else {
//            printf("unknown command line argument '%s', try '%s --help'\n",argv[1],argv[0]);
//            return 1;
            load_program(argv[1]);
            //return 0;
        }
    }

    printProgram();
    printf("Ninja Virtual Machine started\n");
    run();
    printf("Ninja Virtual Machine stopped\n");

    return 0;
}

