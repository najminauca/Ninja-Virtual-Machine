//
// Created by Aron Heinecke on 20.04.22.
//

#ifndef KSP_PUBLIC_NJVM_H
#define KSP_PUBLIC_NJVM_H
#include <stdint.h>
#include <stdbool.h>

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
#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22
#define JMP 23
#define BRF 24
#define BRT 25
#define CALL 26
#define RET 27
#define DROP 28
#define PUSHR 29
#define POPR 30
#define DUP 31

#define NEW 32
#define GETF 33
#define PUTF 34
#define NEWA 35
#define GETFA 36
#define PUTFA 37
#define GETSZ 38
#define PUSHN 39
#define REFEQ 40
#define REFNE 41

#define NJVM_VERSION 8

// legacy A1, create an immediate value
#define IMM(x) ((x) & 0x00FFFFFF)// legacy A1, create an immediate value
// legacy A1, encode instruction for manual programm creation
#define ENC(i) (i << 24)
// retrieve immediate as int32_t from uint32_t
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

// aufrufen des MSB eines u/i32
#define MSB (1 << (8 * sizeof(uint32_t) - 1))
// check ob ObjRef ein primitive oder objekt ist
#define IS_PRIMITIVE(objRef) (((objRef)->size & MSB) == 0)
// Anzahl Elemente im Objekt unter beachtung des MSB
#define GET_ELEMENT_COUNT(objRef) ((objRef)->size & ~MSB)
// Auf objekt zugreifen
#define GET_REFS_PTR(objRef) ((ObjRef *) (objRef)->data)

typedef struct ObjRef {
    bool brokenHeart;
    struct ObjRef* forwardPointer;
    uint32_t size;
    unsigned char data[];
} Obj;
typedef Obj* ObjRef;

typedef struct {
    bool isObjRef;
    union {
        ObjRef  objRef;
        int32_t number;
    } u;
} Stackslot;

extern uint32_t *programm_speicher;
extern uint32_t programm_size;

// Stackpointer
extern int sp;
// Programmcounter
extern int pc;
// Framepointer
extern int fp;
// return value register
extern ObjRef rvr;
// for internal debug output when enabled
extern bool debug;

// Exit programm on error, freeing resources, maybe print debug stuff
void error(int status);

#endif //KSP_PUBLIC_NJVM_H
