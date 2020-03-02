#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int start;
    int mid;
    int end;

    start = 0;
    end = size - 1;
    while (start <= end) {
        mid = (start + end) / 2;
        (*count)++;
        if (mx_strcmp(arr[mid], s) < 0)
            start = mid + 1;
        else if (mx_strcmp(arr[mid], s) > 0)
            end = mid - 1;
        else
            return mid;
    }
    *count = 0;
    return -1;
}
