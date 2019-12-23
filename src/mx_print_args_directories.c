#include "uls.h"

void mx_print_args_directories(t_App *app) {
    t_lfa *lfa = NULL;

    if (app->args_directories == NULL)
        return;
    lfa = mx_new_lfa(app, "");
    for (t_list *cur = app->args_directories; cur != NULL; cur = cur->next) {
        mx_push_back(&(lfa->list_attr),
            (void *)mx_make_attr_struct((char *)(cur->data), lfa));
    } // produce list of file attributes
    mx_apply_sort(lfa);
    for (t_list *cur = lfa->list_attr; cur != NULL; cur = cur->next) {
        mx_print_one_directory(((t_attr *)(cur->data))->original_name, app);
    } // print contents of directories
    mx_free_lfa(&lfa);
}
