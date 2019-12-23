#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int low = 0;
    int mid;
    int high = size - 1;

    if (!*arr)
        return -1;
    while (low <= high) {
        (*count)++;
        mid = (low + high) / 2;
        if (mx_strcmp(arr[mid], s) == 0)
            return mid;
        else if (mx_strcmp(arr[mid], s) > 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    *count = 0;
    return -1;
}

