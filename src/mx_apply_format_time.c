#include "uls.h"

static time_t check_time(t_lfa *lfa, t_list *cur) {
    time_t time = 0;

    switch (lfa->command[time_type]) {
        case time_type_c:
            time = ((t_attr *)(cur->data))->c_time;
            break;
        case time_type_a:
            time = ((t_attr *)(cur->data))->a_time;
            break;
        case time_type_m:
            time = ((t_attr *)(cur->data))->m_time;
            break;
        case time_type_b:
            time = ((t_attr *)(cur->data))->b_time;
            break;
    }
    return time;
}

static bool check_half_year(time_t t) {
    time_t now = time(NULL);
    time_t half_year = ((365 / 2) * 86400);

    if (t + half_year > now)
        return false;
    else
        return true;
}

static char *shor_format(time_t t) {
    char *res = NULL;
    char *str = mx_strdup((ctime(&(t))) + 4);
    char *tmp = NULL;

    str[mx_strlen(str) - 1] = '\0';
    if (check_half_year(t)) {
        res = mx_strndup(str, 7);
        tmp = res; // to free new res;
        res = mx_strjoin(res, &str[15]);
        free(tmp);
    }
    else
        res = mx_strndup(str, 12);
    free(str);
    return res;
}

void mx_apply_format_time(t_list *row, t_list *cur, t_lfa *lfa) {
    time_t t = check_time(lfa, cur);
    char *s = NULL;

    switch (lfa->command[time_format]) {
        case format_time_full:
            s = mx_strdup((ctime(&(t))) + 4);
            s[mx_strlen(s) - 1] = '\0';
            break;
        case format_time_short:
            s = shor_format(t);
            break;
    }
    mx_push_back(&row, (void *)s);
}
