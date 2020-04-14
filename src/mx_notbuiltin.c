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

void mx_notbuiltin(char **arr, t_trig *trig, char **environ) {
    char *pre = "/bin/";
    char *buff = NULL;
    char **temp = NULL;
    int i = 0;

    //trig->err = 0; // просто так
    buff = mx_strjoin(pre, arr[0]);
    for (i = 0; arr[i] != NULL; i++);
    temp = malloc(sizeof(char*) * i + 1);
    temp[0] = strdup(buff);
    for (i = 1; arr[i] != NULL; i++)
        temp[i] = strdup(arr[i]);
    trig->err = exework(temp, environ);
}
