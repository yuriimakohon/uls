#include "libmx.h"

void mx_printstr(const char *s) {
    int len = 0;

    if (!s)
        return;
    len = mx_strlen(s);
    write(1, s, len);
}

