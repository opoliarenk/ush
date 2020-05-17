#include "../inc/ush.h"

static t_pid *listcreat(pid_t chpid, char **temp) {
    t_pid *newpid = (t_pid*)malloc(sizeof(t_pid));
    int i = 0;
    char **split = NULL;

    while (temp[i])
        i++;
    newpid->name_of_pid = (char**)malloc(sizeof(char*) * i + 1);
    i = 0;
    split = mx_strsplit(temp[i], '/');
    newpid->name_of_pid[i] = mx_strdup(split[mx_strlen_for_2star(split) - 1]);
    mx_del_strarr(&split);
    for (i = 1; temp[i]; i++)
        newpid->name_of_pid[i] = mx_strdup(temp[i]);
    newpid->name_of_pid[i] = NULL;
    newpid->npid = chpid; 
    newpid->next = NULL;
    return newpid;
}

static void push_back(pid_t chpid, char **temp, t_trig *trig) {
    t_pid *newpid = listcreat(chpid, temp);
    t_pid *buff = trig->pids;

    if (buff == NULL) {
        trig->pids = newpid;
        return ;
    }
    while (buff->next != NULL) 
        buff = buff->next;
    buff->next = newpid;
}

static void unknown(char *temp) {
    char *buff = NULL;
    int i;

    for (i = strlen(temp) - 1; temp[i] != '/' && i >= 0; i--);
    buff = mx_strdup(&temp[i + 1]);
    mx_printerr("env: ");
    mx_printerr(buff);
    mx_printerr(": No such file or directory\n");
    free(buff);
}

static int exework(char **temp, char **environ, t_trig *trig) {
    int status;
    pid_t pid = fork();
    int status_err = 1;

    if (pid == 0) {
        if (execve(temp[0], temp, environ) == -1) {
            unknown(temp[0]);
            exit(1);
        }
    }
    else {
        waitpid(pid, &status, WUNTRACED);
        if (WEXITSTATUS(status) == 1)
            status_err = 1;
        else
            status_err = 0;
        if (status == 4735)
            push_back(pid, temp, trig);
    }
    return status_err;
}

void mx_env_unk(char **arr, char **environ, t_trig *trig) {
    char *buff = mx_if_P(trig, arr);
    char **temp = NULL;
    int i = 0;

    if (buff == NULL) 
        return ;
    for (i = 0; arr[i] != NULL; i++);
    temp = (char **)malloc(sizeof(char*) * i + 1);
    temp[0] = strdup(buff);
    for (i = 1; arr[i] != NULL; i++)
        temp[i] = strdup(arr[i]);
    temp[i] = NULL;
    trig->err = exework(temp, environ, trig);
    free(buff);
    mx_del_strarr(&temp);
}

