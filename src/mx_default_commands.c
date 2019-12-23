#include "uls.h"

void mx_default_settings(t_App *app) {
    app->command[recursion] = off;  
    app->command[cfilter] = filter_delhidden;
    app->command[csort] = sort_name;
    app->command[reverse] = off;
    app->command[human] = off;
    app->command[cview] = view_many_per_line;
    app->command[numerically] = off;
    app->command[time_format] = format_time_short;
    app->command[time_type] = time_type_m;
    app->command[col_inode] = off;
    app->command[col_blocks] = off;
    app->command[col_user] = on;
    app->command[col_group] = on;
    app->command[header_dir] = off;
    app->command[header_total] = off;
}
