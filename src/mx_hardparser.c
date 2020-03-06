#include "../inc/ush.h"

int mx_hardparser(char *line,  t_trig *trig) {
    //char *new = mx_ultra_strtrim(line, ' '); // доделать
    char *newl = mx_hardsplit(line); //FREE
    char **mass = mx_delim_space(line); //FREE
    int status_of_work;

    if ((status_of_work = mx_red_pipe(mass, trig)) == 2) {
        mx_builtins(mass, trig);
        status_of_work = trig->err;
    }
    free(newl);
    //mx_del_strarr(&mass);
    return status_of_work; // временно
}
