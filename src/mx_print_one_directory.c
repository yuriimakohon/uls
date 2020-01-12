#include "uls.h"

static void print_recursion(char *dirname, t_App *app, t_lfa **lfa);

void mx_print_one_directory(char *dirname, t_App *app) {
    t_lfa *lfa = NULL;

    if (app->command[recursion])
        print_recursion(dirname, app, &lfa);
    else {
        lfa = mx_produce_list_attr(dirname, app);
            if (lfa->print_permission_denied) {
                app->is_any_error = 1;
                if (app->file_count == 1)
                    mx_print_permission_denied_one_dir(dirname);
                else
                    mx_print_permission_denied(dirname, app);
                app->printed_permision = 1;
                mx_free_lfa(&lfa);
                return;
            }
            mx_apply(lfa, app);
            app->printed_permision = 1;
    }
    mx_free_lfa(&lfa);
}

static void print_recursion(char *dirname, t_App *app, t_lfa **lfa) {
    *lfa = mx_produce_list_attr(dirname, app);
    if ((*lfa)->print_permission_denied) {
        app->is_any_error = 1;
        mx_print_permission_denied(dirname, app);
        app->printed_permision = 1;
        return;
    }
    mx_apply(*lfa, app);
    app->printed_permision = 1;
    app->command[header_dir] = on;
    for (t_list *cur = (*lfa)->list_attr; cur != NULL; cur = cur->next) {
        if (((t_attr *)(cur->data))->is_dir) {
            char *fl = ((t_attr *)(cur->data))->original_name;

            if (mx_is_dot_dotdot(fl))
                continue;
            printf("FILE: %s\n", ((t_attr *)(cur->data))->original_name);
            mx_print_one_directory(((t_attr *)(cur->data))->fullname, app);
        }
    }
}
