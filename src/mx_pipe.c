#include "../inc/ush.h"

static int pipes_f(char **buff, t_trig *trig, t_var **list) {
    int fd[2];

    pipe(fd);
    close(1);
    close(0);
    dup2(fd[1], 1);
    mx_builtins(buff, trig, list);
    close(fd[1]);
    return fd[0];
}

static int pipe_gap(char **buff, t_trig *trig, t_var **list, int fd1) {
    int fd[2];

    dup2(fd1, 0);
    pipe(fd);
    dup2(fd[1], 1);
    mx_builtins(buff, trig, list);
    close(fd1);
    close(fd[1]);
    return fd[0];
}

static char **creator(char **mass) {
    char **temp = NULL;
    int j = 0;
    int count = 0;
    int i = 0;

    while (mass[i] && strcmp(mass[i], "|") != 0) {
        count++;
        i++;
    }
    i = 0;
    temp = (char **)malloc(sizeof(char *) * count + 1);
    while (mass[i] && strcmp(mass[i], "|") != 0) {
        temp[j] = strdup(mass[i]);
        j++;
        i++;
    }
    temp[j] = NULL;
    return temp;
}

static void parser(char **mass, t_trig *trig, t_var **list, int count) {
    char **buff = NULL;
    int i = 0;
    int dissp = count;
    int one_zero_fd[3];

    one_zero_fd[0] = dup(1);
    one_zero_fd[1] = dup(0);
    while (count > 0) {
        buff = creator(&mass[i]);
        if (dissp == count)
            one_zero_fd[2] = pipes_f(buff, trig, list);
        else if (count - 1 == 0)
            mx_pipe_help(one_zero_fd, buff, trig, list);
        else 
            one_zero_fd[2] = pipe_gap(buff, trig, list, one_zero_fd[2]);
        while (mass[i] && strcmp(mass[i], "|") != 0)
            i++;
        i++;
        count--;
        mx_del_strarr(&buff);
    }
}

int mx_pipe(char **mass, t_trig *trig, t_var **list) {
    int status_of_work = 2;
    int count = 0;

    for (int i = 0; mass[i]; i++) {
        if (strcmp(mass[i], "|") == 0) {
            count++;
        }
    }
    if (count != 0) {
        parser(mass, trig, list, count + 1);
        status_of_work = trig->err;
    }
    return status_of_work;
}
