#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    int i = 0;
    int res = 0;

    if (str == NULL)
        return -1;
    while (str[i] != '\0') {
        if (str[i] == c && str[i + 1] != '\0' && str[i + 1] != c)
            res++;
        i++;
    }
    if (str[0] != c && res > 0)
        res++;
    return res;
}
