#include "../inc/libmx.h"

char *mx_ultra_strtrim(const char *str, char c) {
    int i = 0;
    int j = 0;
    char *new = NULL;

    if (str == NULL)
        return new;
    j = mx_strlen(str) - 1;
    while (str[i] == c)
        i++;
    while (str[j] == c)
        j--;
    new = mx_strnew(j - i + 1);
    if (new == NULL)
        return new;
    new = mx_strncpy(new, str + i, j - i + 1);
    return new;
}
