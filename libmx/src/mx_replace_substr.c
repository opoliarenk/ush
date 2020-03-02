#include "../inc/libmx.h"

static void replaser(char *res, const char *replace, int i,
const char *sub) {  
    int len = mx_strlen(replace);

    int j = 0;
    if (mx_strlen(sub) > mx_strlen(replace))
        len = mx_strlen(sub);
    else
        len = mx_strlen(replace);
    for (; j <= len; j++) {
        res[i] = replace[j];
        i++;
    }
}

static int cheker(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace)
        return 0;
    else
        return 1;
}

char *mx_replace_substr(const char *str, const char *sub,
const char *replace) {
    int i = 0;
    int len;
    int counter = 0;
    int subs = mx_count_substr(str, sub);
    char *res;

    if (!cheker(str, sub, replace))
        return NULL;
    len = mx_strlen(sub);
    res = (char *)malloc(mx_strlen(str) - subs * (len + mx_strlen(replace)));
    for (i = 0; str[i]; i++) {
        if (i == mx_skip_substr_index(str, sub, counter)) {
            replaser(res, replace, i, sub);
            i += len - 1;
            counter++;
        }
        else
            res[i] = str[i];
    }
    return res;
}
