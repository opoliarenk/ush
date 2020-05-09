#include "../inc/ush.h"

void mx_fill_trig(t_trig *trig) {
    trig->exit = true;
    trig->err = 0;
    trig->PWD = (char *)malloc(50 * sizeof(char));
    trig->OLDPWD = (char *)malloc(50 * sizeof(char));
    trig->OLDPWD = getenv("PWD");
    trig->PWD = getenv("PWD");
    trig->pids = NULL;
}
