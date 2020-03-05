#include "../inc/ush.h"

static void creat_file_one(char *str, char **mass,  t_trig *trig) {
    int fd;
    int save_fd = dup(1);

    close(1);
    fd = open(str, O_WRONLY | O_TRUNC);
    if (fd == -1)
        fd = open(str, O_CREAT | O_WRONLY);
    dup2(fd, 1);
    ///////
    mx_builtins(mass, trig);
    ///////выполнять функу назара вместо этого мусора!!!Передаю туда mass
    dup2(save_fd, 1);
} 

static void creat_file_add(char *str, char **mass,  t_trig *trig) {
    int fd;
    int save_fd = dup(1);

    close(1);
    fd = open(str, O_APPEND | O_WRONLY);
    if (fd == -1)
        fd = open(str, O_CREAT | O_APPEND | O_WRONLY);
    dup2(fd, 1);
    ///////
    mx_builtins(mass, trig);
    ///////выполнять функу назара вместо этого мусора!!!!Передаю туда mass
    dup2(save_fd, 1);
}

int mx_redir(char **mass, t_trig *trig) {
    char **newmass = NULL;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0 && strcmp(mass[i + 1], ">") == 0) {
            i = i + 1;
            newmass = mx_newfor_bults(mass);
            creat_file_add(mass[i + 1], newmass, trig);
            //break;
            continue;
        }
        if (strcmp(mass[i], ">") == 0) {
            newmass = mx_newfor_bults(mass);
            creat_file_one(mass[i + 1], newmass, trig);
            //break;
        }
    }
    return 0;
}
