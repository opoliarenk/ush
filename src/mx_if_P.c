#include "../inc/ush.h"

static char *binary_which(char *arr) {
    char **bins = mx_strsplit(getenv("PATH"), ':');
    char *buff = NULL;
    char *pre = NULL;
    int fd;

    if (arr[0] != '/') {
        for (int i = 0; bins[i]; i++) {
            pre = mx_strjoin(bins[i], "/");
            buff = mx_strjoin(pre, arr);
            if ((fd = open(buff, O_RDONLY)) != -1) {
                close(fd);
                free(pre);
                mx_del_strarr(&bins);
                return buff;
            }
            free(buff);
            free(pre);
        }
    }
    mx_del_strarr(&bins);
    buff = strdup(arr);
    return buff;
}

char *mx_if_P(t_trig *trig, char **arr) {
    char *buff = NULL;

    if (getenv("PATH") != NULL) {
        buff = binary_which(arr[0]);
        return buff;
    } else {
        write(2, "ush: command not found : ", 26);
        write(2, arr[0], strlen(arr[0]));
        write(2, "\n", 1);
        trig->err = 1;
        return NULL;
    }
}
