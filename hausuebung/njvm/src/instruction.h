//
// Created by dev on 14.05.22.
//

#ifndef NJVM_INSTRUCTION_H

#include <stdint.h>

int add();

int sub();

int mul();

int div();

int mod();

int rdint();

int wrint();

int rdchr();

int wrchr();

int pushg(int32_t imm);

int popg(int32_t imm);

int asf(int32_t imm);

int rsf();

int pushl(int32_t imm);

int popl(int32_t imm);

int ne();

int lt();

int le();

int gt();

int ge();

int jmp(int32_t imm);

int brf(int32_t imm);

int brt(int32_t imm);

int eq();

int call(int32_t imm);

int ret();

int drop(int32_t imm);

int pushr();

int popr();

int dup();


#define NJVM_INSTRUCTION_H

#endif //NJVM_INSTRUCTION_H
