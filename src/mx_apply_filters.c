#include "uls.h"

static bool is_hidden(char *name) {
    bool res = false;

    if (name[0] == '.')
        res = true;
    return res;
}

bool mx_apply_filters_ok(char *filename, t_lfa *lfa) {
    switch (lfa->command[cfilter]) {
        case filter_delhidden:
            if (is_hidden(filename))
                return false;
        case filter_deldir:
            if (mx_is_dot_dotdot(filename))
                return false;
    }
    return true;
}

bool mx_is_dot_dotdot(char *name) {
    if (mx_strcmp(name, ".") == 0 || mx_strcmp(name, "..") == 0)
        return true;
    return false;
}
