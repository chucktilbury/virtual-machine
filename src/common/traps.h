#ifndef TRAPS_H
#define TRAPS_H

#include "vMachine.h"

typedef uint16_t TrapNumType;
typedef enum {
    PRINTV,
    PRINTR,
    PRINTI,
} TrapNumber;

void doTrap(VM* vm, TrapNumType tno);

#endif