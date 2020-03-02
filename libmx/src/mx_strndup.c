#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    int i;
    char *res;

    i = 0;
    res = mx_strnew(n);
    mx_strncpy(res, s1, n);
    return res;
}
