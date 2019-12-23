#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);
    char *result = NULL;

    len = n < len ? n : len;
    result = mx_strnew(len);
    if (result == NULL)
        return NULL;
    return mx_strncpy(result, s1, len);
}

