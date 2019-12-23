#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    unsigned char chr = (unsigned char)c;
    unsigned char *ptr = (unsigned char *)b;

    for (size_t i = 0; i < len; i++)
        ptr[i] = chr;
    return b; 
}

