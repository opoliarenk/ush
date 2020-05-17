#include "../inc/ush.h"

static char **save_copy(char ***environ) {
    char **copy = NULL;
    int i = 0;

    for (; (*environ)[i]; i++);
    copy = (char **)malloc(sizeof(char *) * i + 1);
    for (i = 0; (*environ)[i]; i++)
        copy[i] = strdup((*environ)[i]);
    copy[i] = NULL;
    return copy;
}

static void add_to_env(char ***environ, char *arr) {
    char **copy = save_copy(environ);
    int i = 0;

    mx_del_strarr(environ);
    for (; copy[i]; i++);
    (*environ) = (char **)malloc(sizeof(char *) * (i + 1) + 1);
    for (i = 0; copy[i]; i++)
        (*environ)[i] = strdup(copy[i]);
    (*environ)[i] = strdup(arr);
    (*environ)[i + 1] = NULL;
    mx_del_strarr(&copy);
}

static void replacing(char ***environ, char *buff, char *arr) {
    int guess = 0;

    for (int j = 0; (*environ)[j]; j++) {
        if (mx_find_env((*environ)[j], buff)== 0) {
            free((*environ)[j]);
            (*environ)[j] = strdup(arr);
            guess = 1;
            break;
        }
    }
    if (guess == 0)
        add_to_env(environ, arr);
}

static void create_replace(char *arr, char ***environ) {
    int i = 0;
    char *buff = NULL;
    int j = 0;

    for (; arr[i]; i++)
        if (arr[i] == '=')
            break;
    buff = mx_strnew(i);
    for (; j < i; j++)
        buff[j] = arr[j];
    replacing(environ, buff, arr);
    free(buff);
}

char **mx_env_var(char ***envi, char **arr) {
    char **environ = save_copy(envi);

    for (int i = 1; arr[i]; i++) {
        if (strstr(arr[i], "=") != NULL)
            create_replace(arr[i], &environ);
        else 
            break;
    }
    return environ;
}
