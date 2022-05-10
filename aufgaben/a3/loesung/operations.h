#ifndef OPERATIONS_H
#define OPERATIONS_H

#define HALT 0

#define PUSHC 1
void pushc(int immediate);

#define ADD 2
void add();

#define SUB 3
void sub();

#define MUL 4
void mul();

#define DIV 5
void divnjvm();

#define MOD 6
void mod();

#define RDINT 7
void rdint();

#define WRINT 8
void wrint();

#define RDCHR 9
void rdchr();

#define WRCHR 10
void wrchr();

#define PUSHG 11
void pushg(int i);

#define POPG 12
void popg(int i);

#define ASF 13
void asf(int size);

#define RSF 14
void rsf();

#define PUSHL 15
void pushl(int i);

#define POPL 16
void popl(int i);

#define EQ 17
void eq();

#define NE 18
void ne();

#define LT 19
void lt();

#define LE 20
void le();

#define GT 21
void gt();

#define GE 22
void ge();

#define JMP 23
void jmp(int target);

#define BRF 24
void brf(int target);

#define BRT 25
void brt(int target);

#endif
