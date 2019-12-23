#include "libmx.h"

static void find_breaker(int *k, int *j, char **arr, char *pivot);
static int swap_elemets(char **str1, char **str2);
static void iter_index(int *k, int *j);

int mx_quicksort(char **arr, int left, int right) {
    int counter = 0;

    if (!arr)
        return -1;
    if (left < right) {
        int k = left;
        int j = right;
        char *pivot = arr[(j + k) / 2];

        while (k <= j) {
            find_breaker(&k, &j, arr, pivot);
            if (k <= j) {
                counter += swap_elemets(&arr[k], &arr[j]);
                iter_index(&k, &j);
            }
        }
        counter += mx_quicksort(arr, left, j);
        counter += mx_quicksort(arr, k, right);
    }    
    return counter;
}

static void iter_index(int *k, int *j) {
    (*k)++;
    (*j)--;
}

static int swap_elemets(char **str1, char **str2) {
    char *temp = (*str1);

    if (mx_strlen((*str1)) \
        != mx_strlen((*str2)))
        (*str1) = (*str2);
        (*str2) = temp;
        return 1;
    return 0;
}

static void find_breaker(int *k, int *j, char **arr, char *pivot) {
    while (mx_strlen(arr[(*k)]) \
        < mx_strlen(pivot))
        (*k)++;
    while (mx_strlen(arr[(*j)]) \
        > mx_strlen(pivot))
        (*j)--;
}
