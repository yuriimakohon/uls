#include "uls.h"

static void print_comas_str(char *fWord, char *sWord, t_App *app) {
    mx_printstr(fWord);
    if ((sWord != NULL && !(app->is_file_args)) || app->is_file_args)
        mx_printstr(", ");
}

static void print_eighty_width(char *fWord, char *sWord,
    t_App *app, int *num) {
    if ((*num += mx_strlen(fWord) + 2) > 79) {
        mx_printchar('\n');
        *num = mx_strlen(fWord) + 2;
    }
    print_comas_str(fWord, sWord, app);
}

void mx_view_with_comas(char **names, int width, t_App *app) {
    int num = 0;

    for (int i = 0; names[i] != NULL; i++) {
        if (!(isatty(1)))
            print_eighty_width(names[i], names[i + 1], app, &num);
        else {
            if ((num += mx_strlen(names[i]) + 2) > width - 1) {
                mx_printchar('\n');
                num = mx_strlen(names[i]) + 2;
            }
            print_comas_str(names[i], names[i + 1], app);
        }
    }
    app->is_file_args = false;
    mx_printchar('\n');
    mx_del_strarr(&names);
}
