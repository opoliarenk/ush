#include "../inc/ush.h"

static t_pid *listcreat(pid_t chpid, char **temp) {
    t_pid *newpid = (t_pid*)malloc(sizeof(t_pid));
    int i = 0;

    while (temp[i])
        i++;
    newpid->name_of_pid = (char**)malloc(sizeof(char*) * i + 1);
    for (i = 0; temp[i]; i++) {
        newpid->name_of_pid[i] = mx_strdup(temp[i]);
    }
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

static int exework(char **temp, char **environ, t_trig *trig) {
    int status;
    pid_t pid = fork();
    int status_err = 1;
    
    if (pid == 0) {
        if (execve(temp[0], temp, environ) == -1)
            mx_unknown(temp);
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
    mx_del_strarr(&bins);
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
    trig->err = exework(temp, environ, trig);
    free(buff);
}
