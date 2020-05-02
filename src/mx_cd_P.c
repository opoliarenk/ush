#include "../inc/ush.h"

static void part_for_link(char *path, t_trig *trig)  {
    char *link = mx_strnew(1024);

    readlink(path, link, 1024);
    chdir(link);
    trig->OLDPWD = trig->PWD;
    trig->PWD = link;
    mx_strdel(&link);
}

void mx_cd_P(char *path, t_trig *trig) {
    struct stat lt;

    lstat(path, &lt);
    if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
        part_for_link(path, trig);
    else {
        chdir(path);
        trig->OLDPWD = trig->PWD;
        trig->PWD = path;
    }
}
