#include "libmx.h"

static int my_strcmp(const char *str, const char *sub);

int mx_get_substr_index(const char *str, const char *sub) {
    if (str == NULL || sub == NULL)
        return -2;
    for (int i = 0; str[i] != '\0'; i++)
        if (my_strcmp(&str[i], sub) == 0)
            return i;
    return -1;
}

static int my_strcmp(const char *str, const char *sub) {
    for (int i = 0; sub[i] != '\0'; i++) 
        if (str[i] != sub[i])
            return str[i] - sub[i];
    return 0;
}
