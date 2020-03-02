#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    char *res = NULL;

    if (!s1 && !s2)
        return NULL;
    else if (!s1) {
        res = mx_strnew(mx_strlen(s2));
        res = mx_strcat(res, s2);
    }
    else if (!s2) {
        res = mx_strnew(mx_strlen(s1));
        res = mx_strcat(res, s1);
    }
    else {
        res = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
        res = mx_strcat(res, s1);
        res = mx_strcat(res, s2);
    }
    return res;
}
