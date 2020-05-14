#include "../inc/ush.h"

void mx_cd_s(char *path, t_trig *trig) {
    struct stat lt;

    lstat(path, &lt);
    if ((lt.st_mode & MX_IFMT) == MX_IFDIR) {
        chdir(path);
        free(trig->OLDPWD);
        trig->OLDPWD = strdup(trig->PWD);
        free(trig->PWD);
        trig->PWD = strdup(path);
    }
    else {
        mx_printerr("cd: not a directory: ");
        mx_printerr(path);
        mx_printerr("\n");
        trig->err = 1;
    }
}
