#ifndef DOCOMP_H
#define DOCOMP_H

#include "vMachine.h"
#include "values.h"

void doNot(VM* vm, uint8_t regs);
void doEq(VM* vm, uint8_t regs);
void doNEq(VM* vm, uint8_t regs);
void doLeq(VM* vm, uint8_t regs);
void doGeq(VM* vm, uint8_t regs);
void doLess(VM* vm, uint8_t regs);
void doGtr(VM* vm, uint8_t regs);

#endif