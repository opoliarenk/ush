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
    newmass = malloc(sizeof (char *) * newlen + 1);
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

int mx_redirout(char **mass, t_trig *trig, t_var **list) {
    char **newmass = newfor_bults(mass);
    int status_of_work = 2;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], "<") == 0) {
            if (strcmp(mass[i + 1], "<") == 0) {
                status_of_work = mx_doubl_red(mass[i + 2], newmass, trig , list);
                break;
            }
            while (mass[i + 1] != NULL) 
                i++;                
            status_of_work = open_f(mass[i], newmass, trig, list);
            break;
        }
    }
    return status_of_work;
}
