#include "libmx.h"

void mx_print_strarr(char **arr, const char *delim) {
    if (arr == NULL || *arr == NULL)
        return;
    if (delim == NULL)
        return;
    mx_printstr(arr[0]);
    for (int i = 1; arr[i] != NULL; i++) {
        mx_printstr(delim);
        mx_printstr(arr[i]);
    }
    mx_printchar('\n');
}

