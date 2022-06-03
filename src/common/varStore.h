#ifndef VARIABLES_H
#define VARIABLES_H

#include "system.h"
#include "values.h"

typedef uint32_t VarIdx;

typedef enum {
    ACTIVE,
    DELETED,
} VarStatus;

typedef struct {
    Value val;
    VarStatus status;
    bool isAssigned;
} Variable;

typedef struct {
    Variable* list;
    uint32_t cap;
    uint32_t len;
    uint32_t free_slots;
} VarStore;

void initVarStore(VarStore* store);
void uninitVarStore(VarStore* store);

VarIdx createVar(VarStore* store, ValType type);
VarIdx assignVar(VarStore* store, VarIdx idx, Value val);
VarIdx addVar(VarStore* store, Value val);
Value getVar(VarStore* store, VarIdx idx);
void delVar(VarStore* store, VarIdx idx);

#endif