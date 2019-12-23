#include "libmx.h"

static void print_posnum(int n);

void mx_printint(int n) {
    if (n == -2147483648) {
        write(1, "-2147483648", 11);
        return; 
    }
    if (n < 0) {
        mx_printchar('-');
        n = -n;
    }
    print_posnum(n);
}

static void print_posnum(int n) {
    if (n > 9)
        print_posnum(n / 10);
    mx_printchar(n % 10 + '0');
}

