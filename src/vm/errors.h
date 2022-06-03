#ifndef ERRORS_H
#define ERRORS_H

void fatalError(const char* fmt, ...);
void runtimeError(const char* fmt, ...);
void runtimeWarning(const char* fmt, ...);
int getErrors();
int getWarnings();

#endif