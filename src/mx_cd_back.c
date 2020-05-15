#include "../inc/ush.h"

void mx_cd_back(t_trig *trig) {
    char *buf = NULL;
    char dir[1024];

    chdir(trig->OLDPWD);
    if (strcmp(trig->OLDPWD, "..") == 0
    	|| strcmp(trig->OLDPWD, ".") == 0
        || trig->OLDPWD[0] != '/') {
    	getcwd(dir, 1024);
    	mx_printstr(dir);
    }
    else
    	mx_printstr(trig->OLDPWD);
    mx_printchar(10);
    buf = trig->PWD;
    trig->PWD = trig->OLDPWD;
    trig->OLDPWD = buf;
}
