#include "../inc/ush.h"

static void exework(char **temp, char **environ) {
    pid_t pid = fork();
    
    if (pid == 0) {
        if (execve(temp[0], temp, environ) == -1) {// ERROR HERE
            exit(0);//при удачном оно само выходит, при ошибке надо выходить самим( в ручную)
        }
    } else 
        wait(NULL);
    
}

void mx_notbuiltin(char **arr, t_trig *trig, char **environ) {
    char *pre = "/bin/";
    char *buff = NULL;
    char **temp = NULL;
    int i = 0;

    trig->err = 0; // просто так
    buff = mx_strjoin(pre, arr[0]);
    for (i = 0; arr[i] != NULL; i++);
    temp = malloc(sizeof(char*) * i + 1);
    temp[0] = strdup(buff);
    for (i = 1; arr[i] != NULL; i++)
        temp[i] = strdup(arr[i]);
    exework(temp, environ);
}
