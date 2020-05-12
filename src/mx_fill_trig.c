#include "../inc/ush.h"

void mx_fill_trig(t_trig *trig) {
    trig->exit = true;
    trig->err = 0;
    trig->OLDPWD = getenv("PWD");
    trig->PWD = getenv("PWD");
    trig->pids = NULL;
}
