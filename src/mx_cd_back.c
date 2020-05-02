#include "../inc/ush.h"

void mx_cd_back(t_trig *trig) {
    char *buf;

    chdir(trig->OLDPWD);
    mx_printstr(trig->OLDPWD);
    mx_printchar(10);
    buf = trig->PWD;
    trig->PWD = trig->OLDPWD;
    trig->OLDPWD = buf;
}
