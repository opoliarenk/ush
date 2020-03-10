#include "../inc/ush.h"

typedef struct s_cd{
    bool stop;
    bool back; // flag -
    bool s; //flag s
    bool P; //flag P
}              t_cd;

// static void part_for_link(char *path)  {
//     char *link = mx_strnew(1024);

//     readlink(path, link, 1024);
//     chdir(link);
//     mx_strdel(&link);
// }

void mx_builtin_cd(char **arr, t_trig *trig) {
    int i = 0;
    t_cd *cd = (t_cd *)malloc(sizeof(t_cd));
    struct stat lt;

    //memset(cd, 0, sizeof(t_cd));
    cd->stop = 0;
    cd->back = 0;
    cd->s = 0;
    cd->P = 0;
    if (strcmp(arr[i], "-") == 0 && arr[i + 1]) {
        mx_printerr("cd: string not in pwd: -\n");
        trig->err = 1;
        cd->stop = true;
    }
    while (arr[i] && !cd->stop) {
        if (strcmp(arr[i], "-") == 0) {
            cd->back = 1;
            cd->s = false;
            cd->P = false;
        }
        if (strcmp(arr[i], "-s") == 0)
            cd->s = true;
        if (strcmp(arr[i], "-P") == 0 && !cd->s)
            cd->P = true;
        else
            break;
        i++;
    }
    stat(arr[i], &lt);
    if (!cd->stop) {
        if (cd->back || cd->s || cd->P) {
            if (cd->back) {
                setenv("OLDPWD", getenv("PWD"), 1);
                chdir(getenv("OLDPWD"));
                mx_printstr(getenv("OLDPWD"));
                mx_printchar(10);
                setenv("PWD", getenv("OLDPWD"), 1);
            }
            if (cd->s) {
                
            }
            else if (cd->P) {
                
            }
        }
        else {
            if (arr[1]) {
                chdir(arr[1]);
                setenv("PWD", arr[1], 1);
                mx_printchar(10);
                mx_printstr("kakogo huya vivelos");
                mx_printchar(10);
            }
            else {
                chdir("/");
                setenv("PWD", "/", 1);
            }
        }
    }
}
