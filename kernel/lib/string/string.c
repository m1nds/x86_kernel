#include <stddef.h>
#include "string.h"

unsigned char* memset(void* dest, unsigned char val, size_t count) {
    unsigned char* d = (unsigned char*) dest;

    for (size_t i = 0; i < count; i++)
        d[i] = val;

    return d;
}

