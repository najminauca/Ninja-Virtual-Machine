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

#endif
