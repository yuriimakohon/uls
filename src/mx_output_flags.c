#include "uls.h"

static void apply_flag_m(int *fl) {
    fl[C] = 0;
    fl[l] = 0;
    fl[one] = 0;
    fl[m] = 1;
}

static void apply_flag_1(int *fl) {
    fl[C] = 0;
    fl[l] = 0;
    fl[one] = 1;
    fl[m] = 0;
}

static void apply_flag_l(int *fl) {
    fl[C] = 0;
    fl[l] = 1;
    fl[one] = 0;
    fl[m] = 0;
}

static void apply_flag_C(int *fl) {
    fl[C] = 1;
    fl[l] = 0;
    fl[one] = 0;
}

void mx_output_flags(char *s, int *fl) {
    for (; *s; s++)
        switch (*s) {
        case 'm':
            apply_flag_m(fl);
            break;
        case '1':
            apply_flag_1(fl);
            break;
        case 'l':
            apply_flag_l(fl);
            break;
        case 'C':
            apply_flag_C(fl);
            break;
        }
}
