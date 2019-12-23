
#include "libmx.h"

t_list *mx_create_node(void *data) {
    t_list *p = malloc(sizeof(t_list));

    if (p == NULL)
        return NULL;
    p->data = data;
    p->next = NULL;
    return p;
}

