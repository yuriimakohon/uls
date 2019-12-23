#include "uls.h"

static char *add_spaces(int num) {
    char *res = NULL;
    char *number = mx_itoa(num);

    if (num > 256) {
        free(number);
        number = mx_nbr_to_hex(num);
        res = mx_strjoin("0x0000", number);
        free(number);
    }
    else if (num > 99 && num < 1000)
        res = number;
    else if (num <= 99 && num > 9) {
        res = mx_strjoin(" ", number);
        free(number);
    }
    else {
        res = mx_strjoin("  ", number);
        free(number);
    }
    return res;
}

char *mx_majorminor(t_attr *attr) {
    char *major = add_spaces(attr->major_num);
    char *minor = add_spaces(attr->minor_num);
    char *tmp = mx_strjoin(major, ", ");
    char *res = mx_strjoin(tmp, minor);

    free(major);
    free(minor);
    free(tmp);
    return res;
}
