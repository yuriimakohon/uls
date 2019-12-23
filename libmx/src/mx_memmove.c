#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *dptr = (unsigned char *)dst;
    unsigned char *sptr = (unsigned char *)src;

    if (dptr < sptr)
        while (len--)
            *dptr++ = *sptr++;
    else {
        unsigned char *dlast = dptr + (len - 1);
        unsigned char *slast = sptr + (len - 1);

        while (len--)
            *dlast-- = *slast--;
    }
    return dst;
}

