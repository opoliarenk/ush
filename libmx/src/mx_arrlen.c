#include "../inc/libmx.h"

int mx_arrlen(char **str) {
    int i = 0;

    if (str && *str)
        while (str[i])
            i++;
    return i;
}