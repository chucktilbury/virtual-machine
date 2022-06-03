#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "varStore.h"

void addSym(const char* key, VarIdx idx);
VarIdx symToIdx(const char* key);
Value symToVal(const char*key);
void destroySymTab();
void dumpSymtab();

void pushContext(const  char* name);
void popContext();

#endif