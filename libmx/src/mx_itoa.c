#include "libmx.h"

static int get_len(int number, char flag);
static void fill_str(char **str, int len, int number, char flag);

char *mx_itoa(int number) {
    char *str = NULL;
    char flag = 0;
    int len = 0;

    if (number == -2147483648)
        return mx_strdup("-2147483648");
    if (number < 0) {
        flag = 1;
        number *= -1;
    }
    if (number == 0)
        return mx_strdup("0");
    len = get_len(number, flag);
    str = mx_strnew(len);
    fill_str(&str, len, number, flag);
    return str;
}

static int get_len(int number, char flag) {
    int len = 0;

    while (number != 0) {
        number /= 10;
        len++;
    }
    if (flag)
        len++;
    return len;
}

static void fill_str(char **str, int len, int number, char flag) {
    while (len--) {
        (*str)[len] = (number % 10) + 48;
        number /= 10;
    }
    if (flag)
        (*str)[0] = '-';
}

