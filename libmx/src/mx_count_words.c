#include "libmx.h"

int mx_count_words(const char *str, char delimiter) {
    bool flag = true;
    int count = 0;

    while (*str) {
        if (*str == delimiter)
            flag = true;
        else if (flag) {
            count++;
            flag = false;
        }
        str++;
    }
    return count;
}

