#include "../inc/ush.h"

void mx_pipe_help(int *one_zero_fd, char **buff, t_trig *trig, t_var **list) {
    dup2(one_zero_fd[0], 1);
    dup2(one_zero_fd[2], 0);
    mx_builtins(buff, trig, list);
    close(one_zero_fd[2]);
    dup2(one_zero_fd[1], 0);
}

