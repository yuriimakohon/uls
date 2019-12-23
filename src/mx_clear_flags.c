#include "uls.h"

void mx_clear_flags(int *flags) {
	for (int i = 0; i < size; i++)
		flags[i] = 0;
}

bool mx_cmp_name_r(void *data1, void *data2) {
    if (mx_strcmp(((t_attr *)data1)->file_name,
        ((t_attr *)data2)->file_name) < 0)
        return true;
    else
        return false; 
}

bool mx_cmp_name(void *data1, void *data2) {
    if (mx_strcmp(((t_attr *)data1)->file_name,
        ((t_attr *)data2)->file_name) > 0)
        return true;
    else
        return false; 
}
