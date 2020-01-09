#include "uls.h"

bool mx_cmp_size(void *data1, void *data2) {
    if (((t_attr *)data1)->file_size == ((t_attr *)data2)->file_size)
        return mx_cmp_name(data1, data2);
    else if (((t_attr *)data1)->file_size < ((t_attr *)data2)->file_size)
        return true;
    else
        return false;
}

bool mx_cmp_c_time(void *data1, void *data2) {
    if (((t_attr *)data1)->c_time == ((t_attr *)data2)->c_time)
        return mx_cmp_name(data1, data2);
    else if (((t_attr *)data1)->c_time < ((t_attr *)data2)->c_time)
        return true;
    else
        return false;
}

bool mx_cmp_m_time(void *data1, void *data2) {
    if (((t_attr *)data1)->m_time == ((t_attr *)data2)->m_time)
        return mx_cmp_name(data1, data2);
    else if (((t_attr *)data1)->m_time < ((t_attr *)data2)->m_time)
        return true;
    else
        return false; 
}

bool mx_cmp_a_time(void *data1, void *data2) {
    if (((t_attr *)data1)->a_time == ((t_attr *)data2)->a_time)
        return mx_cmp_name(data1, data2);
    else if (((t_attr *)data1)->a_time < ((t_attr *)data2)->a_time)
        return true;
    else
        return false;
}

bool mx_cmp_b_time(void *data1, void *data2) {
    if (((t_attr *)data1)->b_time == ((t_attr *)data2)->b_time)
        return mx_cmp_name(data1, data2);
    else if (((t_attr *)data1)->b_time < ((t_attr *)data2)->b_time)
        return true;
    else
        return false;
}
