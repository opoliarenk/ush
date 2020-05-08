#include "../inc/ush.h"

static char **newfor_bults(char **mass) {
    int newlen = 0;
    char **newmass = NULL;
    int j = 0;
    
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp("<" , mass[i]) == 0)
            break;
        newlen++;
    }
    newmass = (char **)malloc(sizeof (char *) * newlen + 1);
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp("<" , mass[i]) == 0) {
            break;
        }
        newmass[j++] = strdup(mass[i]);
    }
    newmass[newlen] = NULL;
    return newmass;
}

static int open_f(char *line, char **mass, t_trig *trig, t_var **list) {
    int fd;
    int status_of_work;
    int save_fd = dup(0);

    fd = open(line, O_RDONLY);
    if (fd == -1) {
        perror("ush");
        return fd;
    } 
    close(0);
    dup2(fd, 0);
    mx_builtins(mass, trig, list);
    close(fd);
    dup2(save_fd, 0);
    status_of_work = trig->err;
    return status_of_work;
}

static int changred(char **mass, t_trig *trig, char *str, t_var **list) {
    int fd;
    int save_fd;
    int s_f_w = 1;
    char **newmass = newfor_bults(mass);

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0) {
            save_fd = mx_red_bh(mass, i, str, &fd);
            for (int j = 0; mass[j] != NULL; j++) {
                if (strcmp(mass[j], "<") == 0) {
                    if (strcmp(mass[j + 1], "<") == 0)
                        s_f_w = mx_doubl_red(mass[j + 2], newmass, trig, list);
                    else 
                        s_f_w = open_f(mass[j + 1], newmass, trig, list);
                    break;
                }
            }
            dup2(save_fd, 1);
            break;
        }
    }
    mx_del_strarr(&newmass);
    return s_f_w;
}

int mx_redboth(char **mass, t_trig *trig, t_var **list) {
    int status_of_work;
    char *str = NULL;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0 && strcmp(mass[i + 1], ">") == 0) {
            i++;
            str = strdup(mass[i + 1]);
            break;
        } else if (strcmp(mass[i], ">") == 0) {
            str = strdup(mass[i + 1]);
            break;
        }
    }
    status_of_work = changred(mass, trig, str, list);
    free(str);
    return status_of_work;
}
