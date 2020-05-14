#include "../inc/ush.h"

static int creat_file_one(char *str, char **mass,  t_trig *trig, t_var **list) {
    int fd;
    int save_fd = dup(1);
    int status_err;

    close(1);
    fd = open(str, O_WRONLY | O_TRUNC);
    if (fd == -1)
        fd = open(str, O_CREAT | O_WRONLY);
    dup2(fd, 1);
    mx_builtins(mass, trig, list);
    dup2(save_fd, 1);
    status_err = trig->err;
    return status_err;
} 

static int creat_file_add(char *str, char **mass,  t_trig *trig, t_var **list) {
    int fd;
    int save_fd = dup(1);
    int status_err;

    close(1);
    fd = open(str, O_APPEND | O_WRONLY);
    if (fd == -1)
        fd = open(str, O_CREAT | O_APPEND | O_WRONLY);
    dup2(fd, 1);
    mx_builtins(mass, trig, list);
    dup2(save_fd, 1);
    status_err = trig->err;
    return status_err;
}

int mx_redir(char **mass, t_trig *trig, t_var **list) {
    char **newmass = NULL;
    int status_err = 2;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0 && strcmp(mass[i + 1], ">") == 0) {
            i = i + 1;
            newmass = mx_newfor_bults(mass);
            status_err = creat_file_add(mass[i + 1], newmass, trig, list);
            mx_del_strarr(&newmass);
            break;
        }
        if (strcmp(mass[i], ">") == 0) {
            newmass = mx_newfor_bults(mass);
            status_err = creat_file_one(mass[i + 1], newmass, trig, list);
            mx_del_strarr(&newmass);
            break;
        }
    }
    return status_err;
}
