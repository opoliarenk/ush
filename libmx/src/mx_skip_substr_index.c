#include "../inc/libmx.h"

int mx_skip_substr_index(const char *str, const char *sub, int counter) {
    int i;

    i = 0;
    if (!str || !sub || counter < 0)
            return -2;
    while (*str) {
        if (*str == *sub) {
            if (mx_strncmp(str, sub, mx_strlen(sub)) == 0) {
                if (counter == 0)
                    return i;
                counter--;
            }
        }
        str++;
        i++;
    }
    return -1;
}
