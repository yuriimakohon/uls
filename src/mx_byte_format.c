#include "uls.h"

static void raund_bytes(char *result, double num, off_t res);
static void small_sizes(char *result, double num, off_t res, t_byte *n);

char *mx_byte_format(off_t size, t_byte *n) {
    double num = (double)size;
    off_t res = size / n->b;
    char *result = mx_strdup("0.0");

    if (res > 9) {
        res = size % n->b < n->half_b ? res : res + 1;
        free(result);
        return mx_itoa(res);
    }
    else if (size % n->b == 0)
        result[0] = res + 48;
    else if (size % n->b < 52)
        result[0] = res + 48;
    else if (size % n->b < 100) {
        result[0] = res + 48;
        result[2] = '1';
    }
    else
        small_sizes(result, num, res, n);
    return result;
}

static void small_sizes(char *result, double num, off_t res, t_byte *n) {
    num = num * n->ratio;
    num = (num - res) * 1000;
    if (num < 955)
        raund_bytes(result, num, res);
    else {
        result[0] = res + 49;
        result[2] = '0';
    }
}

static void raund_bytes(char *result, double num, off_t res) {
    char *tmp = mx_itoa((int)num);

    if (tmp[1] > '4' && tmp[0] != '9') {
        tmp[0]++;
        result[0] = res + 48;
        result[2] = tmp[0];
    }
    else if (tmp[1] > '4' && tmp[0] == '9') {
        result[0] = res + 49;
        result[2] = '0';
    }
    else {
        result[0] = res + 48;
        result[2] = tmp[0];
    }
    mx_strdel(&tmp);
}
