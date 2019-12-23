#include "libmx.h"

char *mx_strtrim(const char *str) {
    int left = 0;
    int right = 0;

    if (str == NULL)
        return NULL;
    right = mx_strlen(str) - 1;
    while (mx_isspace(str[left]))
        left++;
    while (mx_isspace(str[right]))
        right--;
    if (right < left)
        return mx_strdup("\0");
    for (int i = 0; i < left; i++)
        str++;
    return mx_strndup(str, right - (left - 1));
}
