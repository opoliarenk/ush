#include "../inc/ush.h"

static void printerr(char *path, t_cd *cd, t_trig *trig) {
    mx_printerr("cd: no such file or directory: ");
    mx_printerr(path);
    mx_printerr("\n");
    trig->err = 1;
    cd->stop = 1;
}

char *mx_part1_4_cd(char **arr, t_trig *trig, t_cd *cd, int i) {
    struct stat lt;
    char *path;

    if (!arr[i])
        path = getenv("HOME");
    else
        path = arr[i];
    if (arr[i] && arr[i + 1] && arr[i + 2]) {
        mx_printerr("cd: too many arguments\n");
        trig->err = 1;
        cd->stop = 1;
    }
    if (lstat(path, &lt) < 0 && !cd->stop)
        printerr(path, cd, trig);
    if (arr[i] && arr[i + 1] && arr[i + 2] == NULL && !cd->stop) {
        printf("%s\n", trig->PWD);
        cd->stop = 1;
    }
    return path;
}
