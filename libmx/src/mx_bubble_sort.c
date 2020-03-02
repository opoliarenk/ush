#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int count = 0;
    char *buf = NULL;

    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size -1; i++) {
            if (mx_strcmp(arr[i], arr[i + 1]) > 0) {
                buf = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = buf;
                count++;
            }
        }
    }
    return count;
}
