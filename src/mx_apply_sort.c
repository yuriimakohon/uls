#include "uls.h"

static void apply_sort(t_lfa *lfa);
static void apply_sort_r(t_lfa *lfa);

void mx_apply_sort(t_lfa *lfa) {
    switch (lfa->command[reverse]) {
        case on:
            apply_sort_r(lfa);
            break;
        case off:
            apply_sort(lfa);
            break;
    }
}

static void apply_sort(t_lfa *lfa) {
    switch (lfa->command[csort]) {
        case sort_size:
            mx_sort_list(lfa->list_attr, mx_cmp_size);
            break;
        case sort_ctime:
            mx_sort_list(lfa->list_attr, mx_cmp_c_time);
            break;
        case sort_mtime:
            mx_sort_list(lfa->list_attr, mx_cmp_m_time);
            break;
        case sort_atime:
            mx_sort_list(lfa->list_attr, mx_cmp_a_time);
            break;
        case sort_btime:
            mx_sort_list(lfa->list_attr, mx_cmp_b_time);
            break;
        case sort_name:
            mx_sort_list(lfa->list_attr, mx_cmp_name);
            break;
    }
}

static void apply_sort_r(t_lfa *lfa) {
    switch (lfa->command[csort]) {
        case sort_size:
            mx_sort_list(lfa->list_attr, mx_cmp_size_r);
            break;
        case sort_ctime:
            mx_sort_list(lfa->list_attr, mx_cmp_c_time_r);
            break;
        case sort_mtime:
            mx_sort_list(lfa->list_attr, mx_cmp_m_time_r);
            break;
        case sort_atime:
            mx_sort_list(lfa->list_attr, mx_cmp_a_time_r);
            break;
        case sort_btime:
            mx_sort_list(lfa->list_attr, mx_cmp_b_time_r);
            break;
        case sort_name:
            mx_sort_list(lfa->list_attr, mx_cmp_name_r);
            break;
    }
}
