#include "../inc/ush.h"

static char **namesc(char **envi) {
    int i = 0;
    char **name = NULL;
    int count = 0;

    for (; envi[i]; i++);
    name = (char **) malloc(sizeof(char *) * i + 1);
    for (i = 0; envi[i]; i++) {
        for (int j = 0; envi[i][j]; j++) {
            if (envi[i][j] == '=')
                break;
            count++;
        }
        name[i] = strndup(envi[i], count);
        count = 0;
    }
    name[i] = NULL;
    return name;
}

static char **values(char **envi, char **names) {
    int i = 0;
    char **value = NULL;
    int count = 0;

    for (; envi[i]; i++);
    value = (char **) malloc(sizeof(char *) * i + 1);
    for (i = 0; envi[i]; i++) {
        value[i] = mx_strnew(strlen(envi[i]) - (strlen(names[i] + 1)));
        for (int j = strlen(names[i]) + 1; envi[i][j]; j++) {
            value[i][count] = envi[i][j];
            count++;
        }
        count = 0;
    }
    value[i] = NULL;
    return value;
}

static char **extra_env(char **environ, char **copy) {
    int extra_c = 0;
    int count = 0;
    int i = 0;
    char **new = NULL;
    char **extra_names = NULL;

    for (; environ[i]; i++);
    count = i;
    for (i = 0; copy[i]; i++);
    extra_c = i;
    if (extra_c > count) {

        new = (char **) malloc (sizeof(char *) * (extra_c - count) + 1);
        for (i = 0; count <= extra_c; i++, count++)
            new[i] = strdup(copy[count]);
        new[i] = NULL;
        extra_names = namesc(new);
        mx_del_strarr(&new);
    }
    return extra_names;
}

void mx_env_back(char **environ, char **copy) {
    char **name = namesc(environ);
    char **val = values(environ, name);
    char **extra = extra_env(environ, copy);

    for (int i = 0; environ[i]; i++)
        setenv(name[i], val[i], 1);
    if (extra) {
        for (int i = 0; extra[i]; i++)
            unsetenv(extra[i]);
        mx_del_strarr(&extra);
    }
    mx_del_strarr(&name);
    mx_del_strarr(&val);
}
