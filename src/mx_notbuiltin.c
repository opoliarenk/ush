#include "../inc/ush.h"

static t_pid *listcreat(pid_t chpid, char **temp) {
    t_pid *newpid = (t_pid*)malloc(sizeof(t_pid));
    int i = 0;
    char **split = NULL;

    while (temp[i])
        i++;
    newpid->name_of_pid = (char**)malloc(sizeof(char*) * i + 1);
    split = mx_strsplit(temp[0], '/');
    mx_printstr("ush: suspended ");
    mx_printstr(split[mx_strlen_for_2star(split) - 1]);
    mx_printstr("\n");
    newpid->name_of_pid[0] = mx_strdup(split[mx_strlen_for_2star(split) - 1]);
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

static int exework(char **temp, char **environ, t_trig *trig) {
    int status;
    pid_t pid = fork();
    int status_err = 1;

    if (pid == 0) {
        if (execve(temp[0], temp, environ) == -1) {
            mx_unknown(temp);
            exit(0);
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

static void if_coms(char ***temp) {
    int len = 0;

    for(int i = 0; (*temp)[i]; i++) {
        if ((*temp)[i][0] == '\'' || (*temp)[i][0] == '\"') {
            len = strlen((*temp)[i]);
            if ((*temp)[i][len - 1] != '\'' || (*temp)[i][len - 1] != '\"')
                continue;
        }
        if ((*temp)[i][0] == '\"' || (*temp)[i][0] == '\'')
            mx_last_coms(&(*temp)[i]);
    }
}

void mx_notbuiltin(char **arr, t_trig *trig, char **environ) {
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
    if_coms(&temp);
    trig->err = exework(temp, environ, trig);
    mx_del_strarr(&temp);
    free(buff);
}
