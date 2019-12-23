#include "libmx.h"

char *mx_strdup(const char *str) {
    int len = mx_strlen(str);
    char *dup = mx_strnew(len);
    char *result = mx_strcpy(dup, str);

    return result;
}

