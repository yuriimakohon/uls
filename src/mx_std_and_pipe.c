#include "uls.h"

static char **array_of_names(t_list *list, int size) {
    char **res = (char **)malloc(sizeof(char *) * (size + 1));
    int i = 0;

    for (t_list *j = list; j != NULL; j = j->next, i++)
        res[i] = mx_strdup(j->data);
    res[size] = NULL;
    return res;
}

static void non_standart(t_list *list, char **names) {
    for (t_list *j = list; j != NULL; j = j->next) {
        mx_printstr(j->data);
        mx_printchar('\n');
    }
    mx_del_strarr(&names);
}

void mx_std_and_pipe(t_lfa *lfa, t_App *app) {
    t_stdinfo *info = mx_create_info_struct(lfa->list_attr);
    t_list *some = mx_list_of_lines(lfa);
    t_list *lines = mx_printable_lines(some, info->aligned, lfa);
    char **names = array_of_names(lines, info->listSize);

    mx_terminal_size(info, lines, lfa);
    if (lfa->command[cview] == view_with_commas)
        mx_view_with_comas(names, info->term_width, app);
    else if (isatty(1) && lfa->command[cview] != view_one_per_line)
        mx_print_names(names, info);
    else if (lfa->command[cview] == view_many_per_line)
        mx_print_names(names, info);
    else
        non_standart(lines, names);
    mx_free_list_strings(lines);
    mx_free_raw_lines(&some);
    free(info->aligned);
    info->aligned = NULL;
    free(info);
    info = NULL;
}
