//
// Created by dev on 21.04.22.
//

#ifndef KSP_PUBLIC_PROGRAMME_H
#define KSP_PUBLIC_PROGRAMME_H
const uint32_t prog_1[] = {
        ENC(PUSHC) | IMM(3),
        ENC(PUSHC) | IMM(4),
        ENC(ADD),
        ENC(PUSHC) | IMM(10),
        ENC(PUSHC) | IMM(6),
        ENC(SUB),
        ENC(MUL),
        ENC(WRINT),
        ENC(PUSHC) | IMM(10),
        ENC(WRCHR),
        ENC(HALT)
};

const uint32_t prog_2[] = {
        ENC(PUSHC) | IMM(-2),
        ENC(RDINT),
        ENC(MUL),
        ENC(PUSHC) | IMM(3),
        ENC(ADD),
        ENC(WRINT),
        ENC(PUSHC) | IMM('\n'),
        ENC(WRCHR),
        ENC(HALT)
};

const uint32_t prog_3[] = {
        ENC(RDCHR),
        ENC(WRINT),
        ENC(PUSHC) | IMM('\n'),
        ENC(WRCHR),
        ENC(HALT)
};

#endif //KSP_PUBLIC_PROGRAMME_H
