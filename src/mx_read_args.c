#include "uls.h"

static enum e_arg_type pars_errno(char *name, struct stat sb);

static bool check_valid_file(char *name) {
    if (name[mx_strlen(name) - 1] == '/')
        return false;
    return true;
}

static enum e_arg_type try_argv(char *name, t_App *app) {
    DIR *d = NULL;
    struct stat sb;

    lstat(name, &sb);
    d = opendir(name);
    if (d != NULL) {
        if (S_ISLNK(sb.st_mode) && check_valid_file(name)
            && app->command[cview] == view_long_format) {
            closedir(d);
            return is_file;
        }
        closedir(d);
        return is_directory;
    }
    else
        return pars_errno(name, sb);
}

static enum e_arg_type pars_errno(char *name, struct stat sb) {
    if (errno == EACCES)
        return is_directory;
    if ((errno == ENOTDIR && check_valid_file(name))
        || (S_ISLNK(sb.st_mode) && errno == ENOENT))
        return is_file;
    return is_error;
}

static void args_apply(t_App *app) {
    if (app->args_error == NULL 
        && app->args_files == NULL && app->args_directories == NULL) {
        char *cur_dur_str = ".";
        
        mx_push_back(&(app->args_directories), cur_dur_str);
    }
    if (app->args_files && app->args_directories)
        app->is_file_args = true;
}

void mx_read_args(int argc, char *argv[], t_App *app) {
    bool is_one_dir = false;

    for (int i = app->is_any_flags; i < argc; i++) {
        if (try_argv(argv[i], app) == is_error) {
            mx_push_back(&(app->args_error), argv[i]);
            app->file_count--;
        }
        else if (try_argv(argv[i], app) == is_file) {
            mx_push_back(&(app->args_files),  argv[i]);
            app->command[header_dir] = on;
        }
        else if (try_argv(argv[i], app) == is_directory) {
            if (is_one_dir)
                app->command[header_dir] = on;
            is_one_dir = true;
            mx_push_back(&(app->args_directories),  argv[i]);
        }
    }
    args_apply(app);
}
