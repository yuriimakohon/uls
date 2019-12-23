#include "libmx.h"

char *mx_file_to_str(const char *file) {
    char buf[1024];
    int res;
    char *old_s = NULL;
    int fd = open(file, O_RDONLY);
    char *new_s = NULL;

    if (fd < 0)
        return NULL;
    while ((res = read(fd, buf, 1024)) > 0) {
        buf[res] = '\0';
        old_s = new_s;
        new_s = mx_strjoin(new_s, buf);
        free(old_s);
    }
    close(fd);
    return new_s;
}

