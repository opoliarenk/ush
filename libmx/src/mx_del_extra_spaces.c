#include "../inc/libmx.h"

static void newstr(char *buf, char *res) {
    int i = 0;
    int j = 0;

    while (buf[i] != '\0') {
        if (mx_is_space(buf[i]) == 0) {
            res[j] = buf[i];
            j++;
        }
        if (buf[i + 1] != '\0' && mx_is_space(buf[i]) == 1 
            && mx_is_space(buf[i - 1]) == 0) {
            res[j] = ' ';
            j++;
        }
        i++;
    }
}

char *mx_del_extra_spaces(const char *str) {
    char *buf = mx_strtrim(str);
    char *res;
    int i = 0;
    int j = 0;
    int space = 0;

    if (buf == NULL)
        return NULL;
    while (buf[i++] != '\0') {
        if (mx_is_space(buf[i]) == 0)
            j++;
        if (mx_is_space(buf[i + 1]) == 1 && buf[i + 1] != '\0' 
            && mx_is_space(buf[i]) == 0)
            space++;
    }
    res = mx_strnew(j + space + 1);
    newstr(buf, res);
    mx_strdel(&buf);
    return res;
}
