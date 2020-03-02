#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int i;

    i = 0;
    if (!str || !sub)
        return -2;
    while (*str) {
        if (*str == *sub) {
            if (mx_strncmp(str, sub, mx_strlen(sub)) == 0)
                return i;
        }
        str++;
        i++;
    }
    return -1;
}
