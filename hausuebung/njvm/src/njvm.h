#ifndef NJVM_H
#define NJVM_H

#define MAX 10000

extern unsigned int *programm_speicher;
extern int stack[MAX];
extern int sp;
extern int pc;
extern int pcSize;
extern int fSize;
extern int fp;
extern int *sda;
extern int sdaSize;
extern int runBool;
extern int quit;
extern int returnRegister;

void run();
void print();

#endif
