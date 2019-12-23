#include "uls.h"

static void push_lfa(t_list **row, t_list *cur) {
    mx_push_back(row, mx_strdup(((t_attr *)(cur->data))->inode));
    mx_push_back(row, mx_itoa(((t_attr *)(cur->data))->blocks));
    mx_push_back(row, mx_strdup(((t_attr *)(cur->data))->chmod));
    mx_push_back(row, mx_itoa((int)((t_attr *)(cur->data))->links));
    mx_push_back(row, mx_strdup(((t_attr *)(cur->data))->user));
    mx_push_back(row, mx_strdup(((t_attr *)(cur->data))->group));
}

static void apply_printmode_flag_l(t_lfa *lfa) {
    t_list *row = NULL;
    t_list *cur = lfa->list_attr;
    
    for (; cur != NULL; cur = cur->next) {
        row = NULL;
        push_lfa(&row, cur);
        if (((t_attr *)(cur->data))->c_or_b == false)
            mx_push_back(&row,
                mx_format_size(((t_attr *)(cur->data))->file_size, lfa));
        else
            mx_push_back(&row,
                mx_majorminor((t_attr *) (cur->data)));
        mx_apply_format_time(row, cur, lfa);
        mx_push_back(&row,
            (void *)mx_strdup(((t_attr *)(cur->data))->file_name));
        mx_push_back(&(lfa->raw_lines), (void *)row);
    }
}

static void apply_formats(t_lfa *lfa, t_App *app) {
    switch (lfa->command[cview]) {
        case view_long_format:
            apply_printmode_flag_l(lfa);
            mx_header_total(lfa);
            mx_print_lines(lfa);
            break;
        case view_one_per_line:
            mx_header_total(lfa);
            mx_std_and_pipe(lfa, app);
            break;
        case view_many_per_line:
            mx_header_total(lfa);
            mx_std_and_pipe(lfa, app);
            break;
        case view_with_commas:
            mx_std_and_pipe(lfa, app);
            break;
    }
}

void mx_apply_printmode(t_lfa *lfa, t_App *app) {
    static bool has_printed_anithing = false;

    lfa->new_line_needed = has_printed_anithing;
    if (app->first_dir_name_needed && lfa->is_dir)
        lfa->command[header_dir] = on;
    mx_header_dir(lfa);
    if (lfa->list_attr == NULL)
        return;
    apply_formats(lfa, app);
    has_printed_anithing = true;
}
