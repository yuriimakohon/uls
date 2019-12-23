#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int len = mx_strlen(s1);

    s1 += len;
    s1 = mx_strcpy(s1, s2);
    s1 -= len;
    return s1;
}

