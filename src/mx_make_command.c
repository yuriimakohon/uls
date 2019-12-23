#include "uls.h"

static void time_and_hiden_files(t_App *app);
static void check_other_flags(t_App *app);
static void check_sort(t_App *app);
static void print_formats(t_App *app);

void mx_make_command(t_App *app) {
    mx_default_settings(app);
    if (!(isatty(1)) && !(app->flags[C])) 
        app->command[cview] = view_one_per_line;
    if (app->flags[R]) {
        app->command[recursion] = on;
        app->command[header_dir] = on;
    }
    print_formats(app);
    time_and_hiden_files(app);
    check_other_flags(app);
    check_sort(app);
    if (app->command[cview] == view_long_format) {
        app->command[header_total] = on;
        if (app->flags[c])
            app->command[time_type] = time_type_c;
    }
}

static void print_formats(t_App *app) {
    if (app->flags[l]) {
        app->command[cview] = view_long_format;
        app->command[header_total] = on;
        if (app->flags[c])
            app->command[time_type] = time_type_c;
    }
    if (app->flags[one])
        app->command[cview] = view_one_per_line;
    if (app->flags[m])
        app->command[cview] = view_with_commas;
    if (app->flags[R]) {
        app->command[recursion] = on;
        app->command[header_dir] = off;
        if (app->flags[l])
            app->command[header_total] = on;
        app->command[cfilter] = filter_delhidden;
    }
}

static void time_and_hiden_files(t_App *app) {
    if (app->flags[a])
        app->command[cfilter] = filter_nofilter;
    if (app->flags[A])
        app->command[cfilter] = filter_deldir;
    if (app->flags[t]) {
        app->command[csort] = sort_mtime;
        if (app->flags[c]) {
            app->command[csort] = sort_ctime;
            app->command[time_type] = time_type_c;
        }
        if (app->flags[u])
            app->command[csort] = sort_atime;
        if (app->flags[U])
            app->command[csort] = sort_btime;
    }
    if (app->flags[u])
        app->command[time_type] = time_type_a;
    if (app->flags[U])
        app->command[time_type] = time_type_b;
}

static void check_other_flags(t_App *app) {
    if (app->flags[s]) {
        app->command[col_blocks] = on;
        app->command[header_total] = on;
    }
    if (app->flags[o]) {
        app->command[col_group] = off;
        app->command[cview] = view_long_format;
    }
    if (app->flags[g]) {
        app->command[col_user] = off;
        app->command[cview] = view_long_format;
    }
    if (app->flags[n]) {
        app->command[numerically] = on;
        app->command[cview] = view_long_format;
    }
    if (app->flags[r])
        app->command[reverse] = on;
    if (app->flags[h])
        app->command[human] = on;
}

static void check_sort(t_App *app) {
    if (app->flags[S])
        app->command[csort] = sort_size;
    if (app->flags[f]) {
        app->command[csort] = sort_nosort;
        app->command[cfilter] = filter_nofilter;
    }
    if (app->flags[k])
        app->command[kilobytes] = on;
    if (app->flags[T])
        app->command[time_format] = format_time_full;
    if (app->flags[i])
        app->command[col_inode] = on;
}
