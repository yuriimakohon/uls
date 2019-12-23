#include "uls.h"

static void print_total(t_lfa *lfa);
static void print_dir_name(t_lfa *lfa);

void mx_header_dir(t_lfa *lfa) {
    switch (lfa->command[header_dir]) {
        case on:
            print_dir_name(lfa);
            break;
        case off:
            break;
    }
}

void mx_header_total(t_lfa *lfa) {
    switch (lfa->command[header_total]) {
        case on:
            print_total(lfa);
            break;
        case off:
            break;
    }
}

static void print_total(t_lfa *lfa) {
    unsigned long total = 0;

    for (t_list *cur = lfa->list_attr; cur != NULL; cur = cur->next)
        total += ((t_attr *)(cur->data))->blocks;
    mx_printstr("total ");
    mx_printint(total);
    mx_printstr("\n");
}

static void print_dir_name(t_lfa *lfa) {
    if (lfa->new_line_needed)
        mx_printstr("\n");
    mx_printstr(lfa->dir_path);
    mx_printstr(":\n");
}

