//
// Created by Aron Heinecke on 12.04.22.
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

uint32_t programm_size = 0;
uint32_t *programm_speicher;
// globale variabeln
uint32_t static_data_area_size = 0;
int32_t *static_data_area;
int32_t stack[STACK_LIMIT];
int sp = 0;
int pc = 0;
int fp = 0;
int32_t rvr = 0;

void load_program(const char *path) {
    FILE *fp;
    size_t read_ojects;
    fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Unable to load program from file.");
        exit(1);
    }
    int header_count = 4;
    uint32_t headers[header_count];
    read_ojects = fread(headers, sizeof(uint32_t), header_count, fp);
    if (read_ojects != header_count) {
        printf("ERROR: Could not read a full header for the programm.");
        exit(1);
    }
    programm_size = headers[2];
    static_data_area_size = headers[3];

    //printf("Format %c\n",headers[0]);
    if (headers[0] != 0x46424a4e) {
        printf("ERROR: invalid binary header %x",headers[0]);
        exit(1);
    }
    //printf("Version %d\n",headers[1]);
    if (headers[1] != 4) {
        printf("ERROR: Invalid binary version %d",headers[1]);
        exit(1);
    }
    //printf("Number of instructions %d\n",programm_size);
    //printf("Static variables %d\n",static_data_area_size);
    static_data_area = malloc(static_data_area_size);
    // TODO: größe aufschreiben
    programm_speicher = malloc(programm_size);
    read_ojects = fread(programm_speicher, sizeof(uint32_t), programm_size, fp);
    if (read_ojects != programm_size) {
        printf("ERROR: Mismatch of instruction size header and file length!");
        exit(1);
    }
    fclose(fp);

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
    fp = 0;
    rvr = 0;
    while (1) {
        uint32_t ins = programm_speicher[pc];
        pc = pc + 1;
        count = count + 1;
        if (execute(ins)) {
            break;
        }
    }
    //printf("Finished after %d cycles\n", count);
}

void help(char* binary_name) {
    printf("usage: %s [options] <code file>\n", binary_name);
    printf("\t --version   show version and exit\n");
    printf("\t --help      show this help and exit\n");
}

int main(int argc, char *argv[]) {
    int debug = 0;
    if (argc > 1) {
        int i;
        for(i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                help(argv[0]);
                return 0;
            } else if (strcmp(argv[i], "--version") == 0) {
                printf("Ninja Virtual Machine version %d (compiled %s, %s)\n", VERSION, __DATE__, __TIME__);
                return 0;
            } else if (strcmp(argv[i], "--debug") == 0) {
                debug = 1;
            } else if(i == argc -1) {
                load_program(argv[i]);
            } else {
                printf("ERROR: Unknown argument `%s`",argv[i]);
                return 1;
            }
        }
    } else {
        help(argv[0]);
        return 0;
    }

    //printProgram();
    printf("Ninja Virtual Machine started\n");
    run();
    printf("Ninja Virtual Machine stopped\n");

    free(programm_speicher);
    free(static_data_area);
    return 0;
}

