#include "../inc/ush.h"

static char *create_replace(char *arr) {
    int i = 0;
    char *buff = NULL;
    int j = 0;

    for (; arr[i]; i++)
        if (arr[i] == '=')
            break;
    buff = mx_strnew(i);
    for (; j < i; j++)
        buff[j] = arr[j];
    return buff;
}

int mx_find_env(char *environ, char *buff) {
    char *temp = NULL;

    temp = create_replace(environ);
    if (strcmp(temp, buff) == 0) {
        free(temp);
        return 0;
    }
    free(temp);
    return 1;
}
