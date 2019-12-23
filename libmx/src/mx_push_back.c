#include "libmx.h"

void mx_push_back(t_list **head, void *data) {
    t_list *new_node = NULL;

    if (head == NULL)
        return;
    new_node = mx_create_node(data);
    if (*head == NULL)
        *head = new_node;
    else {
        t_list *cur = NULL;

        for(cur = *head; cur->next != NULL; cur = cur->next);
        cur->next = new_node;
    }
}

