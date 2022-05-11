#ifndef EXECUTE_H
#define EXECUTE_H

#define IMMEDIATE(x) ((x) & 0x00FFFFFF)
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

void printNum(int i);

void execute(unsigned int ir);

void listProg(unsigned int ir, int pc);

#endif
