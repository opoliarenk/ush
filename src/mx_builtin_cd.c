#include "../inc/ush.h"

static void without_flags(char *path, t_trig *trig) {
    chdir(path);
    free(trig->OLDPWD);
    trig->OLDPWD = strdup(trig->PWD);
    free(trig->PWD);
    trig->PWD = strdup(path);
}

void mx_builtin_cd(char **arr, t_trig *trig) {
    int i;
    t_cd *cd = (t_cd *)malloc(sizeof(t_cd));
    char *path;

    memset(cd, 0, sizeof(t_cd));
    trig->is_cdP = 0;
    i = mx_parser_4_cd(arr, trig, cd);
    path = mx_part1_4_cd(arr, trig, cd, i);
    if (!cd->stop) {
        if (cd->back)
            mx_cd_back(trig);
        else if (cd->s)
            mx_cd_s(path, trig);
        else if (cd->P)
            mx_cd_P(path, trig);
        else
            without_flags(path, trig);
    }
    free(cd);
    cd = NULL;
}
