#include "libmx.h"

void mx_del_strarr(char ***arr) {
    char ***p = NULL;
    char **pp = NULL;

    if (arr == NULL || *arr == NULL)
        return;
    p = arr;
    pp = *arr;
    while (**p != NULL) {
        mx_strdel(*p);
        (*p)++;
    }
    free(pp);
    *arr = NULL;
}

