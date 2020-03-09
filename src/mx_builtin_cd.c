#include "../inc/ush.h"

void mx_builtin_cd(char **arr, t_trig *trig) {
    char *buf = arr[1];
    int i = 1;
    char *pwd = mx_strnew(40);
    bool stop = false;

    if (mx_strlen_for_2star(arr) > 3) {
        mx_printerr("cd: too many arguments\n");
        trig->err = 1;
        stop = true;
    }
    if (strcmp(arr[i], "-") == 0 && arr[i + 1]) {
        mx_printerr("cd: string not in pwd: -\n");
        trig->err = 1;
        stop = true;
    }
    while (arr[i] && !stop) {
        if (strcmp(arr[i], "-") == 0) {
            if (!trig->last_cd) {
                getcwd(pwd, 1024);
                mx_printstr(pwd);
            }
            else
                mx_printstr(trig->last_cd);
            mx_printchar(10);
        }
        else
            break;
        i++;        
    }
    if (!stop) {
        if (arr[1]) {
            chdir(buf);
            trig->last_cd = buf;
        }
        else {
            chdir("/");
            trig->last_cd = "/";
        }
    }
}
