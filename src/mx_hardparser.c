#include "../inc/ush.h"

int mx_hardparser(char *line,  t_trig *trig) {
    char *cuts = mx_cut_spaces(line);
    mx_printstr(cuts);
    mx_printint(100);
    char *newl = mx_hardsplit(cuts); //FREE
    mx_printchar('\n');
    mx_printstr(newl);
    mx_printchar('\n');
    char **mass = mx_delim_space(newl); //FREE
    int status_of_work;

    int i = 0;
    while (mass[i] != NULL) {
        mx_printstr(mass[i]);
        mx_printchar('\n');
        i++;
    } //nado budet ubrat
    
    if ((status_of_work = mx_red_pipe(mass, trig)) == 2) {
        mx_builtins(mass, trig);
        status_of_work = trig->err;
    }
    free(newl);
    //mx_del_strarr(&mass);
    return status_of_work; // временно
}
