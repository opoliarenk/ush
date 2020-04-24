#include "../inc/ush.h"

typedef struct s_pwd{
    bool stop;
    bool L;
    bool P;
}              t_pwd;

static void part_for_link(char *path)  {
    char *link = mx_strnew(1024);

    readlink(path, link, 1024);
    mx_printstr(link);
    mx_printstr("\n");
    mx_strdel(&link);
}

void mx_builtin_pwd(char **arr, t_trig *trig) {
    char *cwd = trig->PWD;
    int i = 1;
    int j = 1;
    t_pwd *pwd = (t_pwd *)malloc(sizeof(t_pwd));
    struct stat lt;

    memset(pwd, 0, sizeof(t_pwd));
    while (arr[i]) {
        if (arr[i][0] == '-') {
            j = 1;
            while (arr[i][j]) {
                if (arr[i][j] == 'P')
                    pwd->P = 1;
                else if (arr[i][j] == 'L') {
                    if (!pwd->P)
                        pwd->L = 1;
                }
                else {
                    mx_printerr("pwd: bad option: ");
                    mx_printchar(arr[i][j]);
                    mx_printerr("\n");
                    trig->err = 1;
                    pwd->stop = 1;
                    break;
                }
                j++;
            }
        }
        else {
            mx_printerr("pwd: too many arguments\n");
            trig->err = 1;
            pwd->stop = 1;
            break;
        }
        i++;
    }
    if (!pwd->stop) {
        lstat(cwd, &lt);
        if (pwd->P) {
            if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
                part_for_link(cwd);
            else {
                mx_printstr(cwd);
                mx_printstr("\n");
            }
        }
        else {
            mx_printstr(cwd);
            mx_printstr("\n");
        }
    }
}
