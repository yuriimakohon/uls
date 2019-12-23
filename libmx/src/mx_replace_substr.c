#include "libmx.h"

static char *make_rep_str(int count, const char *s, const char *r, char *str);
static void return_begin(char **rep_str, char **begin);

char *mx_replace_substr(const char *str, const char *sub, \
    const char *replace) {
    int sub_count = mx_count_substr(str, sub);
    char *rep_str = NULL;
    char *begin = NULL;
    int sub_index = 0;

    if (sub_count <= 0)
        return mx_strdup(str);
    rep_str = make_rep_str(sub_count, sub, replace, (char *)str);
    begin = rep_str;
    while (sub_count--) {
        sub_index = mx_get_substr_index(str, sub);
        rep_str = mx_strncpy(rep_str, str, sub_index);
        rep_str += sub_index;
        rep_str = mx_strcpy(rep_str, replace);
        rep_str += mx_strlen(replace);
        str += sub_index + mx_strlen(sub);
    }
    rep_str = mx_strcpy(rep_str, str);
    return_begin(&rep_str, &begin);
    return rep_str;
}

static void return_begin(char **rep_str, char **begin) {
    *rep_str = *begin;
    mx_strdel(&(*begin));
}

static char *make_rep_str(int count, const char *s, const char *r, char *str) {
    int sub_len = count * mx_strlen(s);
    int rep_len = count * mx_strlen(r);
    int rep_str_len = mx_strlen(str) - sub_len + rep_len;
    char *rep_str = mx_strnew(rep_str_len);

    return rep_str;
}

