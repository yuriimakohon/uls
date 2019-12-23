#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    int k = 0;
    char *temp = NULL;
    char *trimed = NULL;

    if (str == NULL)
        return NULL;
    temp = mx_strnew(mx_strlen(str));
    for (int i = 0; str[i]; i++) {
        if (mx_isspace(str[i])
            && !mx_isspace(str[i - 1])) {
            temp[k] = ' ';
        }
        else if (!mx_isspace(str[i]))
            temp[k] = str[i];
        k++;
    }
    trimed = mx_strtrim(temp);
    mx_strdel(&temp);
    return trimed;
}


