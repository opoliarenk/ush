#include "../inc/libmx.h"

static void newstr(char *buf, char *res, char c) {
    int i = 0;
    int j = 0;

    while (buf[i] != '\0') {
        if (buf[i] != c) {
            res[j] = buf[i];
            j++;
        }
        if (buf[i + 1] != '\0' && buf[i] == c && buf[i - 1] != c) {
            res[j] = c;
            j++;
        }
        i++;
    }
    res[j] = c;
}

static void counter(const char *str, char c, int *j, int *space) {
    int i = 0;

    while (str[i++] != '\0') {
        if (str[i] != c)
            (*j)++;
        if (str[i + 1] == c && str[i + 1] != '\0' && str[i] != c)
            (*space)++;
    }
}

char *mx_ultra_del_extra_spaces(const char *str, char c) {
    char *buf;
    char *res;
    int space = 0;
    int j = 0;

    buf = mx_ultra_strtrim(str, c);
    counter(buf, c, &j, &space);
    res = mx_strnew(j + space + 2);
    newstr(buf, res, c);
    mx_strdel(&buf);
    return res;
}
