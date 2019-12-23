#include "uls.h"

t_list *mx_list_of_lines(t_lfa *app) {
    t_list *row = NULL;
    t_list *res = NULL;
    t_list *cur = app->list_attr;

    for (; cur != NULL; cur = cur->next) {
        mx_push_back(&row, mx_strdup(((t_attr *)(cur->data))->inode));
        mx_push_back(&row, mx_itoa(((t_attr *)(cur->data))->blocks));
        mx_push_back(&row,
            (void *)mx_strdup(((t_attr *)(cur->data))->file_name));
        mx_push_back(&res, (void *)row);
        row = NULL;
    }
    return res;
}

t_stdinfo *mx_create_info_struct(t_list *list) {
    t_stdinfo *info = (t_stdinfo *) malloc(sizeof(t_stdinfo));

    info->aligned = (int *) malloc(sizeof(int) * 4);
    info->aligned[0] = 1;
    info->aligned[1] = 1;
    info->aligned[2] = 0;
    info->aligned[3] = 0;
    info->listSize = mx_list_size(list);
    info->maxStr = 0;
    return info;
}
