#ifndef FILEIO_H
#define FILEIO_H

#include "vMachine.h"

void initVM(VM* vm);
void uninitVM(VM* vm);
void saveVM(VM* vm, const char* fname);
void loadVM(VM* vm, const char* fname);

#endif