#include "uls.h"

static char first_type(struct stat sb) {
    return S_ISREG(sb.st_mode) ? '-'
        : S_ISDIR(sb.st_mode) ? 'd'
        : S_ISBLK(sb.st_mode) ? 'b'
        : S_ISCHR(sb.st_mode) ? 'c'
        : S_ISLNK(sb.st_mode) ? 'l'
        : S_ISFIFO(sb.st_mode) ? 'p'
        : S_ISSOCK(sb.st_mode) ? 's'
        : S_ISWHT(sb.st_mode) ? 'w'
        : '?';
}

static char at_plus_space(char *file) {
    acl_t acl = acl_get_file(file, ACL_TYPE_EXTENDED);
    ssize_t xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
    char chr = ' ';

    if (xattr > 0)
        chr = '@';
    else if (acl != NULL)
        chr = '+';
    acl_free(acl);
    return chr;
}

char *mx_eleven_chars_code(struct stat sb, char *file) {
    char *res = mx_strnew(11);

    res[0] = first_type(sb);
    res[1] = (S_IRUSR & sb.st_mode) ? 'r' : '-';
    res[2] = (S_IWUSR & sb.st_mode) ? 'w' : '-';
    res[3] = (S_ISUID & sb.st_mode) ? ((S_IXUSR & sb.st_mode) ? 's' : 'S')
        : ((S_IXUSR & sb.st_mode) ? 'x' : '-');
    res[4] = (S_IRGRP & sb.st_mode) ? 'r' : '-';
    res[5] = (S_IWGRP & sb.st_mode) ? 'w' : '-';
    res[6] = (S_ISGID & sb.st_mode) ? ((S_IXGRP & sb.st_mode) ? 's' : 'S')
        : ((S_IXGRP & sb.st_mode) ? 'x' : '-');
    res[7] = (S_IROTH & sb.st_mode) ? 'r' : '-';
    res[8] = (S_IWOTH & sb.st_mode) ? 'w' : '-';
    res[9] = (S_ISVTX & sb.st_mode) ? ((S_IXOTH & sb.st_mode) ? 't' : 'T')
        : (S_IXOTH & sb.st_mode) ? 'x' : '-';
    res[10] = at_plus_space(file);
    return res;
}

char *mx_get_user(uid_t uid) {
    struct passwd *pws;
    
    pws = getpwuid(uid);
    return mx_strdup(pws->pw_name);
}

char *mx_get_group(gid_t gid) {
    struct group *g;

    if ((g = getgrgid(gid)) != NULL)
        return mx_strdup(g->gr_name);
    else
        return mx_itoa(gid);
}
