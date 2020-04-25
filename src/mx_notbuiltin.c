#include "../inc/ush.h"

static int exework(char **temp, char **environ) {
    int status;
    pid_t pid = fork();
    int status_err = 1;
    
    if (pid == 0) {
        if (execve(temp[0], temp, environ) == -1) {
            mx_unknown(temp);
        }
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        if (WEXITSTATUS(status) == 1) {
            status_err = 1;
        }
        else {
            status_err = 0;
        }
    }
    return status_err;
}

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
                return buff;
            }
            free(buff);
            free(pre);
        }
    }
    return arr;
}

void mx_notbuiltin(char **arr, t_trig *trig, char **environ) {
    char *buff = binary_which(arr[0]);
    char **temp = NULL;
    int i = 0;

    for (i = 0; arr[i] != NULL; i++);
    temp = (char **)malloc(sizeof(char*) * i + 1);
    temp[0] = strdup(buff);
    for (i = 1; arr[i] != NULL; i++)
        temp[i] = strdup(arr[i]);
    temp[i] = NULL;
    trig->err = exework(temp, environ);
    free(buff);
}
