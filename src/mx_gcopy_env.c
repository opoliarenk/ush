#include "../inc/ush.h"

char **mx_gcopy_env(char **environ) {
    char **new = NULL;
    int i = 0;

    for (; environ[i]; i++);
    new = (char **)malloc(sizeof(char *) * i + 1);
    for (i = 0; environ[i]; i++)
        new[i] = strdup(environ[i]);
    new[i] = NULL;
    return new;
}

