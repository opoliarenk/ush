#include "../inc/ush.h"

static void part_for_link(char *path)  {
    char *link = mx_strnew(1024);

    readlink(path, link, 1024);
    mx_printstr("/");
    mx_printstr(link);
    mx_printstr("\n");
    mx_strdel(&link);
}

static void print_pwd(char *cwd, t_trig *trig) {
    char dir[1024];

    if (strcmp(cwd, "..") == 0
        || strcmp(cwd, ".") == 0
        || cwd[0] != '/') {
        getcwd(dir, 1024);
        mx_printstr(dir);
    }
    else {
        if (trig->is_cdP)
            mx_printstr("/");
        mx_printstr(cwd);
    }
    mx_printstr("\n");
}

void mx_builtin_pwd(char **arr, t_trig *trig) {
    t_pwd *pwd = (t_pwd *)malloc(sizeof(t_pwd));
    struct stat lt;

    memset(pwd, 0, sizeof(t_pwd));
    mx_parser_4_pwd(arr, pwd, trig);
    if (!pwd->stop) {
        if (pwd->P)
            lstat(trig->PWD, &lt);
        else
            stat(trig->PWD, &lt);
        if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
            part_for_link(trig->PWD);
        else
            print_pwd(trig->PWD, trig);
    }
    free(pwd);
    pwd = NULL;
}
