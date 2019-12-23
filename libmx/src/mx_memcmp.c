#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    size_t i = 1;
    
    while (*((unsigned char *)s1) == *((unsigned char *)s2) && i < n) {
        if (*((unsigned char *)s1) == '\0' || *((unsigned char *)s2) == '\0')
            return *((unsigned char *)s1) - *((unsigned char *)s2);
        s1 = (unsigned char *)s1 + 1;
        s2 = (unsigned char *)s2 + 1;
        i++;
    }
    return *((unsigned char *)s1) - *((unsigned char *)s2);
}

