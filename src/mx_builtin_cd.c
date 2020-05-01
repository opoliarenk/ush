#include "../inc/ush.h"

typedef struct s_cd{
    bool stop;
    bool back;
    bool s;
    bool P;
}              t_cd;

static int mx_parser_4_cd(char **arr, t_trig *trig, t_cd *cd) {
    int i = 1;
    int j = 0;

    while (arr[i]) {
        if (strcmp(arr[i], "-") == 0 && arr[i + 1]) {
            mx_printerr("cd: string not in pwd: -\n");
            trig->err = 1;
            cd->stop = true;
            break;
        }
        if (strcmp(arr[i], "-") == 0) {
            cd->back = 1;
            cd->s = false;
            cd->P = false;
        }
        else {
            if (arr[i][j] == '-') {
                j++;
                while (arr[i][j]) {
                    if (arr[i][j] == 's')
                        cd->s = 1;
                    else if (arr[i][j] == 'P') {
                        if (!cd->s)
                            cd->P = 1;
                    }
                    else {
                        mx_printerr("cd: no such file or directory: ");
                        mx_printerr(arr[i]);
                        mx_printerr("\n");
                        trig->err = 1;
                        cd->stop = 1;
                        break;
                    }
                    j++;
                }
                    j = 0;
            }
            else
                break;
        }
        i++;
    }
    return i;
}

static void part_for_link(char *path, t_trig *trig)  {
    char *link = mx_strnew(1024);

    readlink(path, link, 1024);
    chdir(link);
    trig->OLDPWD = trig->PWD;
    trig->PWD = link;
    mx_strdel(&link);
}

void mx_builtin_cd(char **arr, t_trig *trig) {
    int i;
    t_cd *cd = (t_cd *)malloc(sizeof(t_cd));
    struct stat lt;
    char *buf;
    char *path;

    memset(cd, 0, sizeof(t_cd));
    i = mx_parser_4_cd(arr, trig, cd);
    if (cd->stop)
        mx_printstr("\nstop = 1\n");
    if (cd->s)
        mx_printstr("\ns = 1\n");
    if (cd->P)
        mx_printstr("\nP = 1\n");
    if (cd->back)
        mx_printstr("\nback = 1\n");
    
    if (!arr[i])
        path = getenv("HOME");
    else
        path = arr[i];
    if (arr[i + 1] && arr[i + 2] && arr[i + 3]) {
        mx_printerr("cd: too many arguments\n");
        trig->err = 1;
        cd->stop = 1;
    }
    if (lstat(path, &lt) < 0 && !cd->stop) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(path);
        mx_printerr("\n");
        trig->err = 1;
        cd->stop = 1;
    }
    if (!cd->stop) {
        if (cd->back) {
            chdir(trig->OLDPWD);
            mx_printstr(trig->OLDPWD);
            mx_printchar(10);
            buf = trig->PWD;
            trig->PWD = trig->OLDPWD;
            trig->OLDPWD = buf;
        }
        else if (cd->s) {
            if ((lt.st_mode & MX_IFMT) == MX_IFDIR) {
                chdir(path);
                trig->OLDPWD = trig->PWD;
                trig->PWD = path;
            }
            else {
                mx_printerr("cd: not a directory: ");
                mx_printerr(path);
                mx_printerr("\n");
                trig->err = 1;
            }
        }
        else if (cd->P) {
            if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
                part_for_link(path, trig);
            else {
                chdir(path);
                trig->OLDPWD = trig->PWD;
                trig->PWD = path;
            }
        }
        else {
            chdir(path);
                trig->OLDPWD = trig->PWD;
                trig->PWD = path;
            }
    }
    // mx_printstr("\nPWD : ");
    // mx_printstr(trig->PWD);
    // mx_printstr("\nOLDPWD : ");
    // mx_printstr(trig->OLDPWD);
    // mx_printstr("\n");
}
