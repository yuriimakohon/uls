#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    void *new = NULL;

    if (!ptr && size) {
        new = malloc(size);
        if (!new)
            return NULL;
    }
    else {
        if (malloc_size(ptr) < size) {
            new = malloc(size);
            if (!new)
                return NULL;
            mx_memcpy(new, ptr, \
                malloc_size(ptr));
            free(ptr);
        }
        else
            new = ptr;
    }
    return new;
}

