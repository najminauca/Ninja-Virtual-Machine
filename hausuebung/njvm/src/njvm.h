//
// Created by dev on 20.04.22.
//

#ifndef KSP_PUBLIC_NJVM_H
#define KSP_PUBLIC_NJVM_H
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
#define PUSHG 11
#define POPG 12
#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16

#define IMM(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))
#define ENC(i) (i << 24)

//#define PROGRAM_LIMIT 1000
#define STACK_LIMIT 1000

extern uint32_t *programm_speicher;//[PROGRAM_LIMIT];
extern uint32_t programm_size;
// globale variabeln
extern uint32_t static_data_area_size;
extern int32_t *static_data_area;
extern int32_t stack[STACK_LIMIT];
// Stackpointer
extern int sp;
// Programmcounter
extern int pc;
// Framepointer
extern int fp;

#endif //KSP_PUBLIC_NJVM_H
