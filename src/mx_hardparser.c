#include "../inc/ush.h"

int mx_hardparser(char *line,  t_trig *trig) {
    char *newl = mx_hardsplit(line); //FREE
    char **mass = mx_sh_splite(newl); //FREE

    if (mx_red_pipe(mass, trig) == 2) {
        mx_builtins(mass, trig);
    }
    return 1; // временно
}
