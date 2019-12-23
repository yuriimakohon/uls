#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, \
    size_t little_len) {
    unsigned char *bptr = NULL;
    unsigned char *lptr = NULL;

    if (big_len >= little_len && big_len != 0
        && little_len != 0) {
        bptr = (unsigned char *)big;
        lptr = (unsigned char*)little;
        while (big_len--) {
            if (mx_memcmp(bptr, lptr, little_len) == 0)
                return bptr;
            bptr++;
        }
    }
    return NULL;
}
 
