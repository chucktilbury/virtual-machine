#ifndef DOJUMPS_H
#define DOJUMPS_H

#include "vMachine.h"
#include "values.h"

void doCall(VM* vm, Value val);
void doRCall(VM* vm, Value val);
void doJmp(VM* vm, Value val);
void doRJmp(VM* vm, Value val);
void doBr(VM* vm, Value val);
void doRBr(VM* vm, Value val);
void doReturn(VM* vm);

#endif