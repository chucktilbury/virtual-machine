
#include "system.h"
#include "errors.h"
#include <stdarg.h>

static int num_errors = 0;
static int num_warnings = 0;

void runtimeError(const char* fmt, ...)
{
    va_list args;
    fprintf(stderr, "runtime error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
    num_errors++;
}

void runtimeWarning(const char* fmt, ...)
{
    va_list args;
    fprintf(stderr, "runtime warning: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
    num_warnings++;
}

void fatalError(const char* fmt, ...)
{
    va_list args;
    fprintf(stderr, "fatal error: ");

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);
    num_errors++;
    exit(1);
}

int getErrors()
{
    return num_errors;
}

int getWarnings()
{
    return num_warnings;
}