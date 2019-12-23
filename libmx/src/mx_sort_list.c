#include "libmx.h"

t_list *mx_sort_list(t_list *head, bool (*cmp)(void *, void *)) {
    if (!head)
        return NULL;
    for (t_list *i = head; i->next != NULL; i = i->next) {
        t_list *m = i;
        void *t = NULL;

        for (t_list *j = i->next; j != NULL; j = j->next)
            if (cmp(m->data, j->data))
                m = j;
        t = m->data;
        m->data = i->data;
        i->data = t;
    }
    return head;
}

