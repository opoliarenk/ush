#include "../inc/libmx.h"

char *mx_strdup(const char *s1) {
    char *res;

    res = mx_strnew(mx_strlen(s1));
    res = mx_strcpy(res, s1);
    return res;
}
