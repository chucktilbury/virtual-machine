#ifndef CALLSTACK_H
#define CALLSTACK_H

#include "system.h"
#include "values.h"

typedef struct {
    uint32_t ret_addr;
    Value arity;
    Value* parameters;
} __attribute__((packed)) CallStackElem;

typedef struct {
    CallStackElem* list;
    uint32_t cap;
    uint32_t len;
} CallStack;

void initCallStack(CallStack* store);
void uninitCallStack(CallStack* store);
void pushCallStack(CallStack* store, CallStackElem cse);
CallStackElem peekCallStack(CallStack* store);
CallStackElem popCallStack(CallStack* store);

#endif
