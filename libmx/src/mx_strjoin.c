#include "libmx.h"

static char *is_null(const char *s1, const char *s2);

char *mx_strjoin(const char *s1, const char *s2) {
    int len = 0;
    char *result = NULL;
    int i = 0;
    int j = 0;

    if (s1 == NULL || s2 == NULL)
        return is_null(s1, s2);
    len = mx_strlen(s1) + \
        mx_strlen(s2);
    result = mx_strnew(len);
    for (i = 0; i < mx_strlen(s1); i++)
        result[i] = s1[i];
    for (j = i; j < len; j++) {
        result[j] = *s2;
        s2++;
    }
    return result;
}

static char *is_null(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;
    else if (s1 == NULL)
        return mx_strdup(s2);
    else
        return mx_strdup(s1);
}

