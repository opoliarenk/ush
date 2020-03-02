#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    int i = 0;
    int j = 0;
    char *new = NULL;

    if (str == NULL)
        return new;
    j = mx_strlen(str) - 1;
    while (mx_is_space(str[i]) == 1)
        i++;
    while (mx_is_space(str[j]) == 1)
        j--;
    new = mx_strnew(j - i + 1);
    if (new == NULL)
        return new;
    new = mx_strncpy(new, str + i, j - i + 1);
    return new;
}
