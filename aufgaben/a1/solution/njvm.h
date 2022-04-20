//
// Created by dev on 20.04.22.
//

#ifndef KSP_PUBLIC_NJVM_H
#include <stdint.h>

#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10

#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))
#define ENC(i) (i << 24)

const uint32_t prog_1[] = {
        ENC(PUSHC) | 3,
        ENC(PUSHC) | 4,
        ENC(ADD),
        ENC(PUSHC) | 10,
        ENC(PUSHC) | 6,
        ENC(SUB),
        ENC(MUL),
        ENC(WRINT),
        ENC(PUSHC) | 10,
        ENC(WRCHR),
        ENC(HALT)
};

const uint32_t prog_2[] = {
        ENC(PUSHC) | -2,
        ENC(RDINT),
        ENC(MUL),
        ENC(PUSHC) | 3,
        ENC(ADD),
        ENC(WRINT),
        ENC(PUSHC) | '\n',
        ENC(WRCHR),
        ENC(HALT)
};

const uint32_t prog_3[] = {
        ENC(RDCHR),
        ENC(WRINT),
        ENC(PUSHC) | '\n',
        ENC(WRCHR),
        ENC(HALT)
};

#define PROGRAM_LIMIT 1000
#define STACK_LIMIT 1000

uint32_t programm_speicher[PROGRAM_LIMIT];
int32_t stack[STACK_LIMIT];
int sp = 0;
int pc = 0;

#define KSP_PUBLIC_NJVM_H

#endif //KSP_PUBLIC_NJVM_H
