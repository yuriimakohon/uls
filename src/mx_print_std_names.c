#include "uls.h"

static void max_len(t_list *listStr, int *maxStr) {
    for (t_list *j = listStr; j != NULL; j = j->next) {
        if (mx_strlen(j->data) > (*maxStr))
            *maxStr = mx_strlen(j->data);
    }
}

static int my_ceil(float num) {
    int inum = (int)num;

    if (num == (float)inum) {
        return inum;
    }
    return inum + 1;
}

static void print_spaces(int num) {
    for (int d = 0; d < num; d++) {
        mx_printchar('\t');
    }
}

void mx_terminal_size(t_stdinfo *info, t_list *lines, t_lfa *app) {
    struct winsize win;
    int rows = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    max_len(lines, &info->maxStr);
    if (app->command[cview] == view_many_per_line && !(isatty(1)))
        info->cols = 80 > info->maxStr
            ? 80 / (info->maxStr + 8 - (info->maxStr % 8)) : 1;
    else {
        if (win.ws_col > info->maxStr)
            info->cols = win.ws_col / (info->maxStr + 8 - (info->maxStr % 8));
        else
            info->cols = 1;
    }
    rows = my_ceil((float)((float)info->listSize / (float)info->cols));
    if (rows == 0)
        info->rows = 1;
    else
        info->rows = rows;
    info->term_width = win.ws_col;
}

void mx_print_names(char **names, t_stdinfo *info) {
    int num = 0;

    for (int i = 0; i < info->rows; i++) {
        for (int j = 0; i + j < info->listSize; j += info->rows) {
            mx_printstr(names[i + j]);
            num = ((info->maxStr / 8) + 1) - ((mx_strlen(names[i + j]) / 8));
            if (i + j < info->listSize - info->rows)
                print_spaces(num);
        }
        mx_printchar('\n');
    }
    mx_del_strarr(&names);
}
