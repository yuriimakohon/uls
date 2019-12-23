#include "uls.h"

t_lfa *mx_produce_list_attr(char *dirname, t_App *app) {
    t_lfa *lfa = mx_new_lfa(app, dirname);              
    DIR *d = opendir(dirname);

    if (d != NULL) {
        struct dirent *entry;
        
        lfa->is_dir = true;
        while ((entry = readdir(d)) != NULL) {
            if (mx_apply_filters_ok(entry->d_name, lfa))
                mx_push_back(&(lfa->list_attr),
                    mx_make_attr_struct((entry->d_name), lfa));
        }
        closedir(d);
    }
    else
        lfa->print_permission_denied = true;
    return lfa;
}
