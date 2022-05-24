#ifndef OPERATIONS_H
#define OPERATIONS_H

#define HALT 0

#define PUSHC 1
void pushc(int immediate);

#define ADD 2
void add(void);

#define SUB 3
void sub(void);

#define MUL 4
void mul(void);

#define DIV 5
void divnjvm(void);

#define MOD 6
void mod(void);

#define RDINT 7
void rdint(void);

#define WRINT 8
void wrint(void);

#define RDCHR 9
void rdchr(void);

#define WRCHR 10
void wrchr(void);

#define PUSHG 11
void pushg(int i);

#define POPG 12
void popg(int i);

#define ASF 13
void asf(int size);

#define RSF 14
void rsf(void);

#define PUSHL 15
void pushl(int i);

#define POPL 16
void popl(int i);

#define EQ 17
void eq(void);

#define NE 18
void ne(void);

#define LT 19
void lt(void);

#define LE 20
void le(void);

#define GT 21
void gt(void);

#define GE 22
void ge(void);

#define JMP 23
void jmp(int target);

#define BRF 24
void brf(int target);

#define BRT 25
void brt(int target);

#define CALL 26
void call(int target);

#define RET 27
void ret(void);

#define DROP 28
void drop(int n);

#define PUSHR 29
void pushr(void);

#define POPR 30
void popr(void);

#define DUP 31
void dup(void);

#endif
