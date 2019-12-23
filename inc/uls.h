#ifndef ULS_H
#define ULS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <dirent.h>
#include <errno.h>
#include "libmx.h"

typedef struct s_byte { // For flag -h
    int b;
    int half_b;
    double ratio;
} t_byte;

typedef struct s_attr {
    char *inode;
    char *chmod;
    char *user;
    char *group;
    char *file_name;
    char *original_name;
    char *fullname;
    blkcnt_t blocks;      /* blocks allocated for file */
    nlink_t links;        /* number or hard links to the file */
    off_t file_size;      /* file size, in bytes */
    time_t a_time;        /* [XSI] Time of last access */
    time_t m_time;
    time_t c_time;
    time_t b_time;
    bool is_dir;
    bool c_or_b;
    int major_num;
    int minor_num;
} t_attr;

enum e_attr {
    at_inode,
    at_blocks,
    at_chmod,       
    at_links,
    at_user,
    at_group,
    at_file_size,
    at_time,
    at_file_name,
    at_MAX
};

typedef enum {
    off,
    on,
    filter_nofilter,
    filter_delhidden,
    filter_deldir,
    filter_onlydir,
    sort_nosort,
    sort_size,
    sort_ctime,
    sort_mtime,
    sort_atime,
    sort_btime,
    sort_name,
    format_time_full,
    format_time_short,
    time_type_c,
    time_type_a,
    time_type_m,
    time_type_b,
    view_long_format,		/* -l and other options that imply -l */
    view_one_per_line,		/* -1 */
    view_many_per_line,		/* -C */
    view_horizontal,		/* -x */
    view_with_commas,		/* -m */
} e_Command_State;

typedef enum {
    recursion,
    cfilter,
    csort,
    reverse,
    human,
    time_format,
    time_type,
    cview,
    header_dir,    // for -R
    header_total,  // for -l
    numerically,   // -n
    kilobytes,     // -k
    col_inode,     // -i
    col_blocks,    // -s
    col_user,      // -g
    col_group,     // -o
    MAX_COMMANDS
} e_Command;

typedef enum e_flag {  // Done 22 flags
    minus,
    one, //  +1  -- single column output
    l, //  +l  -- bacik case..
    A, //  +A  -- list all except . and ..
    C, //  +C  -- list entries in columns sorted vertically
    R, //  +R  -- list subdirectories recursively
    S, //  +S  -- sort by size
    T, //  +T  -- show complete time information
    U, //  +U  -- use creationg time
    a, //  +a  -- list entries starting with .
    c, //  +c  -- status change time
    f, //  +f  -- output is not sorted
    g, //  +g  -- long listing but without owner information
    h, //  +h  -- print sizes in human readable form
    i, //  +i  -- print file inode numbers
    k, //  +k  -- print sizes of 1k
    m, //  +m  -- comma separated
    n, //  +n  -- numeric uid, gid
    r, //  +r  -- reverse sort order
    s, //  +s  -- display size of each file in blocks
    t, //  +t  -- sort by modification time
    o, //  +o  -- hide group
    u, //  +u  -- access time
    size, // number of flags
} t_flag;

typedef struct {
    t_list *list_attr;
    t_list *raw_lines;
    char *dir_path;
    bool is_dir;
    int *command;
    int *al;
    bool print_permission_denied;
    bool new_line_needed;
} t_lfa;

typedef struct {
    int *al; // attributs for aligning
    int *flags;
    int is_any_flags;
    int file_count;
    int command[MAX_COMMANDS];
    t_list *args_error;
    t_list *args_files;
    t_list *args_directories;
    bool first_dir_name_needed;
    bool stop_flag;
    bool is_file_args;
    bool is_any_error;
    bool printed_permision;
} t_App;

// Struct for standart output & pipe
typedef struct {
    int maxStr;
    int rows;
    int cols;
    int listSize;
    int *aligned;
    int term_width;
} t_stdinfo;

enum e_arg_type {
    is_error,
    is_file,
    is_directory
};

t_App *mx_new_app(void);
void mx_clear_flags(int *flags);
void mx_filter_flags(char *argv, int *fl);
void mx_output_flags(char *s, int *fl);
void mx_read_flags(char *s, t_App *app);
void mx_make_command(t_App *app);
void mx_default_settings(t_App *app);
void mx_read_args(int argc, char *argv[], t_App *app);
t_lfa *mx_new_lfa(t_App *app, char *current_dir);
char *mx_byte_format(off_t size, t_byte *n);

// Standart view & pipe & comas
void mx_std_and_pipe(t_lfa *lfa, t_App *app);
void mx_print_names(char **names, t_stdinfo *info);
void mx_terminal_size(t_stdinfo *info, t_list *lines, t_lfa *app);
void mx_view_with_comas(char **names, int width, t_App *app);
t_list *mx_list_of_lines(t_lfa *app);
t_stdinfo *mx_create_info_struct(t_list *list);

// Free
void mx_free_lfa(t_lfa **lfa);
void mx_free_list_strings(t_list *list);
void mx_free_raw_lines(t_list **list);
void mx_free_node_data(t_list *node);

t_lfa *mx_produce_list_attr(char *dirname, t_App *app);
t_attr *mx_make_attr_struct(char *fileName, t_lfa *lfa);
char *mx_get_group(gid_t gid);
char *mx_get_user(uid_t uid);
char *mx_eleven_chars_code(struct stat sb, char *file);
void mx_apply(t_lfa *lfa, t_App *app);
void mx_apply_without_printing(t_lfa *lfa);
void mx_apply_sort(t_lfa *lfa);
bool mx_apply_filters_ok(char *filename, t_lfa *lfa);
void mx_apply_printmode(t_lfa *lfa, t_App *app);
void mx_apply_format_time(t_list *row, t_list *cur, t_lfa *lfa);
bool mx_is_switched_off(int i, t_lfa *lfa);
char *mx_format_size(off_t size, t_lfa *app);

// errors
void mx_print_permission_denied(char *dirname, t_App *app);
void mx_print_permission_denied_one_dir(char *dirname);
void mx_check_error_flag(char *s);
bool mx_is_control_char(char c);

// print
void mx_header_dir(t_lfa *lfa);
void mx_header_total(t_lfa *lfa);
void mx_print_lines(t_lfa *lfa);
t_list *mx_printable_lines(t_list *head, int *a, t_lfa *lfa);
void mx_print_one_directory(char *name, t_App *app);
bool mx_print_args_file(t_App *app);
void mx_print_args_error(t_App *app);
void mx_print_args_directories(t_App *app);
char *mx_del_extra_path(char *str);

/* comparators for sorting commamd*/
bool mx_cmp_size(void *data1, void *data2);
bool mx_cmp_c_time(void *data1, void *data2);
bool mx_cmp_name(void *data1, void *data2);
bool mx_cmp_m_time(void *data1, void *data2);
bool mx_cmp_a_time(void *data1, void *data2);
bool mx_cmp_b_time(void *data1, void *data2);
bool mx_cmp_size_r(void *data1, void *data2);
bool mx_cmp_c_time_r(void *data1, void *data2);
bool mx_cmp_name_r(void *data1, void *data2);
bool mx_cmp_m_time_r(void *data1, void *data2);
bool mx_cmp_a_time_r(void *data1, void *data2);
bool mx_cmp_b_time_r(void *data1, void *data2);

// utils
bool mx_is_dot_dotdot(char *name);
char *mx_majorminor(t_attr *attr);

#endif

