#ifndef ERRORS_H
#define ERRORS_H

void syntaxError(const char* fmt, ...);
void fatalError(const char* fmt, ...);
int getErrors();
int getWarnings();

#endif