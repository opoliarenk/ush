#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    char *str;
    int i;

    i = 0;
    str = (char *)malloc((size + 1) * sizeof(char));
    if (str == NULL)
        return NULL;
    while (i <= size) {
        str[i] = '\0';
        i++;
    }
    return str;
}
