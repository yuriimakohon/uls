#include "uls.h"

void mx_free_node_data(t_list *node) {
    if (node != NULL || node->data != NULL) {
        free((((t_attr *)(node->data))->inode));
        free((((t_attr *)(node->data))->chmod));
        free((((t_attr *)(node->data))->user));
        free((((t_attr *)(node->data))->group));
        free((((t_attr *)(node->data))->file_name));
        free((((t_attr *)(node->data))->original_name));
        free((((t_attr *)(node->data))->fullname));
        free(node->data);
        node->data = NULL;
    }
}

void mx_free_list_attr(t_list **list) {
    t_list *next_node = *list;

    while (next_node != NULL) {
        t_list *cur = next_node;
        
        next_node = next_node->next;
        mx_free_node_data(cur);
        free(cur);
    }
    *list = NULL;
}

void mx_free_list_strings(t_list *list) {
    if (list == NULL)
        return;
    while (list != NULL) {
        mx_strdel((char **)&(list->data));
        mx_pop_front(&list);
    }
}

void mx_free_raw_lines(t_list **list) {
    if (list == NULL)
        return;
    while (*list != NULL) {
        if ((*list)->data != NULL)
            mx_free_list_strings((*list)->data);
        mx_pop_front(list);
    }
}

void mx_free_lfa(t_lfa **lfa) {
    mx_free_list_attr(&((*lfa)->list_attr));
    mx_free_raw_lines(&((*lfa)->raw_lines));
    if ((*lfa)->command)
        free((*lfa)->command);
    if ((*lfa)->dir_path)
        free((*lfa)->dir_path);
    free(*lfa);
    *lfa = NULL;
}
