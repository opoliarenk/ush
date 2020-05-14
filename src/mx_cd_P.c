#include "../inc/ush.h"

static void part_for_link(char *path, t_trig *trig)  {
    char *link = mx_strnew(1024);

    readlink(path, link, 1024);
    chdir(link);
    free(trig->OLDPWD);
    trig->OLDPWD = strdup(trig->PWD);
    free(trig->PWD);
    trig->PWD = strdup(link);
    mx_strdel(&link);
    trig->is_cdP = 1;
}

void mx_cd_P(char *path, t_trig *trig) {
    struct stat lt;

    lstat(path, &lt);
    if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
        part_for_link(path, trig);
    else {
        chdir(path);
        free(trig->OLDPWD);
        trig->OLDPWD = strdup(trig->PWD);
        free(trig->PWD);
        trig->PWD = strdup(path);
    }
}
