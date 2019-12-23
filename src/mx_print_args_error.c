#include "uls.h"

static void lexisort(t_App *app);
static void swap_files_names(t_list **prev, t_list **curr);

static void check_and_print_error(char *name) {
    DIR *d = NULL;
    char *name_short = mx_del_extra_path(name);

    d = opendir(name);
        mx_printerr("uls: ");
    if (errno == EACCES)
        mx_printerr(name_short);
    else
        mx_printerr(name);
    mx_printerr(": ");
    mx_printerr(strerror(errno));
    mx_printerr("\n");
    mx_strdel(&name_short);
}

void mx_print_args_error(t_App *app) {
    app->is_any_error = (app->args_error != NULL) ? 1 : 0;
    if (!app->flags[f] && app->args_error != NULL) {
        lexisort(app);
        app->first_dir_name_needed = true;
    }
    for (t_list *cur = app->args_error; cur != NULL; cur = cur->next)
        check_and_print_error((char *)(cur->data));
}

static void lexisort(t_App *app) {
    t_list *prev = app->args_error;
    t_list *curr = prev->next;
    bool flag = 0;

    while (curr) {
        flag = 0;
        if (mx_strcmp(prev->data, curr->data) > 0) {
            swap_files_names(&prev, &curr);
            flag = 1;
            prev = app->args_error;
            curr = prev->next;
        }
        if (!flag) {
            prev = curr;
            curr = curr->next;
        }
    }
}

static void swap_files_names(t_list **prev, t_list **curr) {
    char *temp = (*curr)->data;

    (*curr)->data = (*prev)->data;
    (*prev)->data = temp;
}
