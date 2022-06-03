#ifndef DOARITH_H
#define DOARITH_H

#include "vMachine.h"
#include "values.h"

void doNeg(VM* vm, uint8_t regs);
void doAdd(VM* vm, uint16_t regs);
void doSub(VM* vm, uint16_t regs);
void doMul(VM* vm, uint16_t regs);
void doDiv(VM* vm, uint16_t regs);
void doMod(VM* vm, uint16_t regs);

#endif