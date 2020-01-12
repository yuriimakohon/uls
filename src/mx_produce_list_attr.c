#include "uls.h"

static int is_not_dir(char *dirname, char* d_name);
static bool is_dir(char *dirname);

t_lfa *mx_produce_list_attr(char *dirname, t_App *app) {
    t_lfa *lfa = mx_new_lfa(app, dirname);
    DIR *d = opendir(dirname);

    if (d != NULL) {
        struct dirent *entry;

        lfa->is_dir = true;
        while ((entry = readdir(d)) != NULL) {
        /*lfa->print_permission_denied = */is_not_dir(dirname, entry->d_name);
            if (mx_apply_filters_ok(entry->d_name, lfa))
                mx_push_back(&(lfa->list_attr),
                    mx_make_attr_struct((entry->d_name), lfa));
        }
        closedir(d);
    }
    else
        lfa->print_permission_denied = 1;
    // for (;lfa->list_attr->next; lfa->list_attr = lfa->list_attr->next)
    return lfa;
}

static int is_not_dir(char *dirname, char* d_name) {
    char *tmp = mx_strjoin(dirname, "/");
    char *str = mx_strjoin(tmp, d_name);
    DIR *dir = opendir(str);
    int retval = 0;

    if (!dir) {
        if (is_dir(str)) {
            retval = 2;
        }
    }
    else
        closedir(dir);
    // printf("dirname = %s is %d\n", str, retval);
    mx_strdel(&tmp);
    mx_strdel(&str);
    return retval;
}

static bool is_dir(char *dirname) {
    struct stat st;
    stat(dirname, &st);

    if (S_ISDIR(st.st_mode))
        return 1;
    return 0;
}
