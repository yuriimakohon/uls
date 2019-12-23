#include "libmx.h"

int mx_list_size(t_list *list) {
    int size = 0;

    for (t_list *cur = list; cur != NULL; cur = cur->next) 
        size++;
    return size;
}

