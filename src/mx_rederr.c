#include "../inc/ush.h"

static char **newfor_bults(char **mass) {
    int newlen = 0;
    char **newmass = NULL;
    int j = 0;
    
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp("2>" , mass[i]) == 0)
            break;
        newlen++;
    }
    newmass = malloc(sizeof (char *) * newlen + 1);
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp("2>" , mass[i]) == 0) {
            break;
        }
        newmass[j++] = strdup(mass[i]);
    }
    newmass[newlen] = NULL;
    return newmass;
}

static int creat_file_one(char *str, char **mass,  t_trig *trig, t_var **list) {
    int fd;
    int save_fd = dup(2);
    int status_err;

    close(2);
    fd = open(str, O_WRONLY | O_TRUNC);
    if (fd == -1)
        fd = open(str, O_CREAT | O_WRONLY);
    dup2(fd, 2);
    mx_builtins(mass, trig, list);
    dup2(save_fd, 2);
    status_err = trig->err;
    return status_err;
} 

static int creat_file_add(char *str, char **mass,  t_trig *trig, t_var **list) {
    int fd;
    int save_fd = dup(2);
    int status_err;

    close(2);
    fd = open(str, O_APPEND | O_WRONLY);
    if (fd == -1)
        fd = open(str, O_CREAT | O_APPEND | O_WRONLY);
    dup2(fd, 2);
    mx_builtins(mass, trig, list);
    dup2(save_fd, 2);
    status_err = trig->err;
    return status_err;
}

int mx_rederr(char **mass, t_trig *trig, t_var **list) {
    char **newmass = NULL;
    int status_err = 2;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], "2>") == 0 && strcmp(mass[i + 1], ">") == 0) {
            i = i + 1;
            newmass = newfor_bults(mass);
            status_err = creat_file_add(mass[i + 1], newmass, trig, list);
            //continue;
            break;
        }
        if (strcmp(mass[i], "2>") == 0) {
            newmass = newfor_bults(mass);
            status_err = creat_file_one(mass[i + 1], newmass, trig, list);
            break;
        }
    }
    return status_err;
}
