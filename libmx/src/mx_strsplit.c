#include "libmx.h"

static char **split_words(int arr_len, const char *s, char c);

char **mx_strsplit(const char *s, char c) {
    int arr_len = 0;
    char **sarr = NULL;
    int index = 0;

    if (!s)
        return NULL;
    arr_len = mx_count_words(s, c);
    sarr = split_words(arr_len, s, c);
    *sarr = NULL;
    sarr -= arr_len;
    return sarr;
}

static char **split_words(int arr_len, const char *s, char c) {
    char **sarr = malloc(sizeof(char *) * arr_len + 1);
    int index = 0;

    for (int i = 0; i < arr_len; i++) {
        while (*s == c)
            s++;
        index = mx_get_char_index(s, c);
        if (i != arr_len - 1)
            *sarr = mx_strndup(s, index);
        else if (mx_get_char_index(s, c) != -1)
            *sarr = mx_strndup(s, index);
        else
            *sarr = mx_strdup(s);
        s += index;
        sarr++;
    }
    return sarr;
}

