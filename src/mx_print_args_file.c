#include "uls.h"

bool mx_print_args_file(t_App *app) {
    t_lfa *lfa = NULL;

    if (app->args_files == NULL)
        return false;
    lfa = mx_new_lfa(app, "./");
    lfa->is_dir = false;
    lfa->command[header_dir] = off;
    lfa->command[header_total] = off;
    for (t_list *cur = app->args_files; cur != NULL; cur = cur->next) {
        mx_push_back(&(lfa->list_attr),
            (void *)mx_make_attr_struct((char *)(cur->data), lfa));
    }
    mx_apply(lfa, app);
    mx_free_lfa(&lfa);
    return true;
}
