#include "../inc/ush.h"

bool mx_check_double(char *arr, char c) {
    int i = 0;

    while (arr[i]) {
        if (arr[i] == c)
            return true;
        i++;
    }
    return false;
}
