#include "uls.h"

static void filter_one(char *s, int *fl);
static void filter_two(char *s, int *fl);

void mx_filter_flags(char *argv, int *fl) {
    filter_one(argv, fl);
    filter_two(argv, fl);
    for (; *argv; argv++) {
        if (*argv == 's')
            fl[s] = 1;
        if (*argv == 'U') {
            fl[U] = 1;
            fl[u] = 0;
        }
        if (*argv == 'g')
            fl[g] = 1;
    }
}

static void filter_one(char *s, int *fl) {
    for (; *s; s++)
        switch (*s)	{
            case 'f':
                fl[f] = 1;
                break;
            case 'h':
                fl[h] = 1;
                break;
            case 'k':
                fl[k] = 1;
                break;
            case 'o':
                fl[o] = 1;
                break;
        }
}

static void filter_two(char *s, int *fl) {
    for (; *s; s++)
        switch (*s)	{
            case 'T':
                fl[T] = 1;
                break;
            case 'i':
                fl[i] = 1;
                break;
            case 'n':
                fl[n] = 1;
                break;
            case 'r':
                fl[r] = 1;
                break;
        }
}
