#ifndef VALSTACK_H
#define VALSTACK_H

#include "system.h"
#include "values.h"

typedef struct {
    Value* list;
    uint32_t cap;
    uint32_t len;
} ValStack;

void initValStack(ValStack* store);
void uninitValStack(ValStack* store);

void pushValStack(ValStack* store, Value value);
Value peekValStack(ValStack* store, int index);
Value popValStack(ValStack* store);
uint32_t valStackIndex(ValStack* store);

#endif
