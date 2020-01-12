#include "uls.h"

char *get_name(struct stat sb,  char *file, char *path, t_lfa *app) {
    char link_read[255];
    ssize_t bytes_read;
    char *res = NULL;
    char *tmp = NULL;

    if (isatty(1))
        for (int i = 0; file[i]; i++)
            if (mx_is_control_char(file[i]))
                file[i] = '?';
    if (S_ISLNK(sb.st_mode) && app->command[cview] == view_long_format) {
        tmp = mx_strjoin(file, " -> ");
        bytes_read = readlink(path, link_read, 254);
        link_read[bytes_read] = '\0';
        res = mx_strjoin(tmp, link_read);
        mx_strdel(&tmp);
    }
    else 
        res = mx_strdup(file);
    return res;
}

static char *stat_path(char *fileName, char *dirName) {
    char *res = NULL;

    if (mx_strcmp(fileName, "/") == 0 || mx_strcmp(dirName, "") == 0
        || fileName[0] == '/') {
        res = mx_strdup(fileName);
    }
    else {
        char *tmp = NULL;
        tmp = mx_strjoin(dirName, "/");
        res = mx_strjoin(tmp, fileName);
        mx_strdel(&tmp);
    }
    return res;
}

static void first_part(
t_attr *attr_struct, t_lfa *lfa,
struct stat sb, char *fullname) {
    attr_struct->inode = mx_itoa(sb.st_ino);
    if (lfa->command[kilobytes] == off)
        attr_struct->blocks = sb.st_blocks;
    else if (lfa->command[kilobytes] == on)
        attr_struct->blocks = sb.st_blocks % 2 == 0 ? sb.st_blocks / 2
           : sb.st_blocks / 2 + 1;
    attr_struct->chmod = mx_eleven_chars_code(sb, fullname);
    attr_struct->links = sb.st_nlink;
    if (lfa->command[numerically] == off) {
        attr_struct->user = mx_get_user(sb.st_uid);
        attr_struct->group = mx_get_group(sb.st_gid);
    }
    else if (lfa->command[numerically] == on){
        attr_struct->user = mx_itoa(sb.st_uid);
        attr_struct->group = mx_itoa(sb.st_gid);
    }
}

static void second_part(t_attr *attr_struct, struct stat sb, char *fullname) {
    attr_struct->file_size = sb.st_size;
    attr_struct->a_time = sb.st_atime;
    attr_struct->m_time = sb.st_mtime;
    attr_struct->c_time =  sb.st_ctime;
    attr_struct->b_time = sb.st_birthtimespec.tv_sec;
    attr_struct->fullname = fullname;
    if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode)) {
        attr_struct->c_or_b = true;
        attr_struct->major_num = major(sb.st_rdev);
        attr_struct->minor_num = minor(sb.st_rdev);
    }
    else {
        attr_struct->c_or_b = false;
        attr_struct->major_num = 0;
        attr_struct->minor_num = 0;
    }
}

t_attr *mx_make_attr_struct(char *fileName, t_lfa *lfa, int not_dir) {
    struct stat sb;
    char *fullname = NULL;
    t_attr *attr_struct = malloc(sizeof(t_attr));

    fullname = stat_path(fileName, lfa->dir_path);
    lstat(fullname, &sb);
    first_part(attr_struct, lfa, sb, fullname);
    second_part(attr_struct, sb, fullname);
    attr_struct->file_name = get_name(sb, fileName, fullname, lfa);
    attr_struct->original_name = mx_strdup(fileName);
    attr_struct->not_dir = not_dir;
    if ((sb.st_mode & S_IFMT) == S_IFDIR)
        attr_struct->is_dir = true;
    else
        attr_struct->is_dir = false;
    return attr_struct;
}
