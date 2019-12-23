#include "uls.h"

void mx_print_permission_denied(char *dirname, t_App *app) {
    char *only_dirname = mx_del_extra_path(dirname);

    if (app->printed_permision == 1)
        mx_printerr("\n");
    mx_printerr(dirname);
    mx_printerr(":\nuls: ");
    mx_printerr(only_dirname);
    mx_printerr(": Permission denied\n");
    mx_strdel(&only_dirname);
}

void mx_print_permission_denied_one_dir(char *dirname) {
    char *only_dirname = mx_del_extra_path(dirname);

    mx_printerr("uls: ");
    mx_printerr(only_dirname);
    mx_printerr(": Permission denied\n");
    mx_strdel(&only_dirname);
}

char *mx_del_extra_path(char *str) {
    char *result = NULL;
    int len = mx_strlen(str);

    if (mx_get_char_index(str, '/') != -1) {
        while (str[--len] != '/');
        result = mx_strdup(str += len + 1);
    }
    else
        result = mx_strdup(str);
    return result;
}
