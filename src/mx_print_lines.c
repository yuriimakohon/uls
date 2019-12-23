#include "uls.h"

void mx_print_lines(t_lfa *lfa) {
    t_list *lines = mx_printable_lines(lfa->raw_lines, lfa->al, lfa);

    for (t_list *i = lines; i != NULL; i = i->next) {
        mx_printstr((char *)(i->data));
        mx_printstr("\n");
    }
    while (lines != NULL) {
        t_list *tmp = lines->next;

        mx_strdel((char **)(&lines->data));
        mx_pop_front(&lines);
        lines = tmp;
    }
}
