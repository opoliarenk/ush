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

static void copyset(char **envi) {
    char **name = namesc(envi);
    char **val = values(envi, name);

    for (int i = 0; envi[i]; i++)
        setenv(name[i], val[i], 1);
    mx_del_strarr(&name);
    mx_del_strarr(&val);
}

static int counte(char **arr) {
    int count = 0;

    for (int i = 1; arr[i]; i++) {
        if (strstr(arr[i], "=") != NULL)
            continue;
        count++;
    }
    return count;
}

int mx_env_exe(char **arr, char **envi, t_trig *trig) {
    int count = 0;
    char **notbuilt = NULL;

    if ((count = counte(arr)) == 0)
        return 1;
    notbuilt = (char **)malloc(sizeof(char *) * count + 1);
    count = 0;
    for (int i = 1; arr[i]; i++) {
        if (strstr(arr[i], "=") != NULL)
            continue;
        notbuilt[count] = strdup(arr[i]);
        count++;
    } 
    notbuilt[count] = NULL;
    copyset(envi);
    mx_env_unk(notbuilt, envi, trig);
    //mx_del_strarr(&notbuilt);
    return 0;
}
