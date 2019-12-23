#include "uls.h"

static void copy_commands(t_App *app, t_lfa *lfa);

t_lfa *mx_new_lfa(t_App *app, char *current_dir) {
    t_lfa *lfa = malloc(sizeof(t_lfa));

    lfa->list_attr = NULL;
    lfa->raw_lines = NULL;
    lfa->print_permission_denied = false;
    lfa->command = malloc(sizeof(int) * MAX_COMMANDS);
    copy_commands(app, lfa);
    lfa->al = (int *)(app->al);
    lfa->dir_path = mx_strdup(current_dir);
    return lfa;
}

static void copy_commands(t_App *app, t_lfa *lfa) {
    for (int i = 0; i < MAX_COMMANDS; i++)
        lfa->command[i] = app->command[i];
}
