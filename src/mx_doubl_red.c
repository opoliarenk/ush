#include "../inc/ush.h"

int mx_doubl_red(char *line, char **mass, t_trig *trig, t_var **list) {
    int pipefd[2];
    int save_zero = dup(0);
    char *temp = NULL;
    char buff[128];

    pipe(pipefd);
    while (1) {
        fgets(buff, 128, stdin);
        temp = mx_cut_spaces(buff);
        if (strcmp(temp, line) == 0)
            break;
        write(pipefd[1], temp, strlen(buff) - 1);
        write(pipefd[1], "\n", 1);
        free(temp);
    }
    free(temp);
    close(pipefd[1]);
    close(0);
    dup2(pipefd[0], 0);
    mx_builtins(mass, trig, list);
    close(pipefd[0]);
    dup2(save_zero, 0);
    return trig->err;
}
