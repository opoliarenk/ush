#include "../inc/ush.h"

static void part_for_link(char *path)  {
    char *link = mx_strnew(1024);

    readlink(path, link, 1024);
    mx_printstr(link);
    mx_printstr("\n");
    mx_strdel(&link);
}

static void print_pwd(char *cwd) {
    char dir[1024];

    if (strcmp(cwd, "..") == 0
        || strcmp(cwd, ".") == 0) {
        getcwd(dir, 1024);
        mx_printstr(dir);
    }
    else
        mx_printstr(cwd);
    mx_printstr("\n");
}

void mx_builtin_pwd(char **arr, t_trig *trig) {
    char *cwd = trig->PWD;
    t_pwd *pwd = (t_pwd *)malloc(sizeof(t_pwd));
    struct stat lt;

    memset(pwd, 0, sizeof(t_pwd));
    mx_parser_4_pwd(arr, pwd, trig);
    if (!pwd->stop) {
        lstat(cwd, &lt);
        if (pwd->P) {
            if ((lt.st_mode & MX_IFMT) == MX_IFLNK)
                part_for_link(cwd);
            else
                print_pwd(cwd);
        }
        else
            print_pwd(cwd);
    }
}
