
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "memory.h"


const char* strings[] = {
    "%d. first string",
    "%d. second string",
    "%d. third string",
    "%d. fourth string",
    "%d. fifth string",
    "%d. sixth string",
    "%d. seventh string",
    "%d. eighth string",
    "%d. ninth string",
    "%d. tenth string",
    "%d. eleventh string",
    "%d. twelfth string",
    NULL
};

void* buffer[50];

void dump()
{
    for(int idx = 0; buffer[idx] != NULL; idx++) {
        if(buffer[idx] != NULL)
            printf("%s\n", (char*)buffer[idx]);
    }
    _dumpMemory();
}

int main() {

    _initMemory();
    memset(buffer, 0, sizeof(buffer));

    int idx = 0;
    for(int x = 0; x < 40; x++) {
        char buf[100];
        sprintf(buf, strings[idx++], x+1);
        buffer[x] = _alloc_str(buf);

        if(strings[idx] == NULL)
            idx = 0;
    }

    dump();

    _free(buffer[5]);
    buffer[5] = "<deleted>";

    _free(buffer[10]);
    buffer[10] = "<deleted>";

    _free(buffer[15]);
    buffer[15] = "<deleted>";

    _free(buffer[16]);
    buffer[16] = "<deleted>";

    dump();

    _free(buffer[0]);
    buffer[0] = "<deleted>";

    _free(buffer[39]);
    buffer[39] = "<deleted>";

    dump();

    _destroyMemory();

    return 0;
}

