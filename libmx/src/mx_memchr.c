#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    for (size_t i = 0; *((unsigned char *)s) != c && i < n; i++)
        s = (unsigned char *)s + 1;
    if (*((unsigned char *)s) == c)
        return (unsigned char *)s;
    else
        return NULL;
}
 
