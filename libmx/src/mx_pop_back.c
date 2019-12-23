#include "libmx.h"

void mx_pop_back(t_list **head) {
    if (head == NULL)
        return;
    if (*head == NULL)
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        t_list *cur = NULL;

        for(cur = *head; cur->next->next != NULL; cur = cur->next);
        free(cur->next);
        cur->next = NULL;
    }
}

