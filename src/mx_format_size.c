#include "uls.h"

static void inicialize_num_kb(t_byte *num) {
    num->b = 1024;
    num->half_b = 512;
    num->ratio = 0.0009765625;
}

static void inicialize_num_mb(t_byte *num) {
    num->b = 1048576;
    num->half_b = 524288;
    num->ratio = 9.53674316e-7;
}

static void inicialize_num_gb(t_byte *num) {
    num->b = 1073741824;
    num->half_b = 536870912;
    num->ratio = 9.3132257e-10;
}

static void flag_h_on(off_t size, char **res, t_byte *num) {
    char *temp = NULL;

    if (size <= 1022976) { 
        inicialize_num_kb(num);
        temp = mx_byte_format(size, num);
        *res = mx_strjoin(temp, "K");
        free(temp);
    }
    else if (size <= 1047527424) {
        inicialize_num_mb(num);
        temp = mx_byte_format(size, num);
        *res = mx_strjoin(temp, "M");
        free(temp);
    }
    else {
        inicialize_num_gb(num);
        temp = mx_byte_format(size, num);
        *res = mx_strjoin(temp, "G");
        free(temp);
    }
}

char *mx_format_size(off_t size, t_lfa *app) {
    char *res = NULL;
    char *sizestr = mx_itoa(size);
    t_byte *num = malloc(sizeof(t_byte));

    switch (app->command[human]) {
        case off:
            res = mx_strdup(sizestr);
            break;
        case on:
            app->al[at_group] = -3;
            if (size <= 999)
                res = mx_strjoin(sizestr, "B");
            else
                flag_h_on(size, &res, num);
            break;
    }
    free(num);
    free(sizestr);
    return res;
}
