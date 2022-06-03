#ifndef VMACHINE_H
#define VMACHINE_H

#include "system.h"
#include "memory.h"
#include "values.h"
#include "varStore.h"
#include "instrStore.h"
#include "callStack.h"
#include "valStack.h"

#define NUM_REGS    16

typedef uint8_t RegNumType;

typedef struct {
    Value registers[NUM_REGS];
    bool nzero;
    VarStore vstore;
    InstrStore istore;
    ValStack vstack;
    CallStack cstack;
} VM;

#endif