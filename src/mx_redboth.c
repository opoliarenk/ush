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
    char *str = NULL;
    int i = 0;
    char **newmass = NULL;
    int j = 0;
    int status_of_work;
    
    fd = open(line, O_RDONLY);
    if (fd == -1) {
        perror("ush"); //ERROR
        return fd;
    } else 
        close(fd);
    str = mx_file_to_str(line);
    while (mass[i])
        i++;
    newmass = malloc (sizeof (char *) * (i + 2));
    for (j = 0; j < i + 2; j++) {
        while (mass[j]) {
            newmass[j] = strdup(mass[j]);
            j++;
        }
        newmass[j] = strdup(str);
    }
    newmass[i + 1] = NULL;
    mx_builtins(newmass, trig, list);
    status_of_work = trig->err;
    return status_of_work;
}

static int changred(char **mass, t_trig *trig, char *str, t_var **list) {
    int fd;
    int save_fd;
    int status_of_work;
    char **newmass = newfor_bults(mass);

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], ">") == 0) {
            save_fd = dup(1);
            close(1);
            fd = open(str, O_WRONLY | O_TRUNC);
            if (fd == -1)
                 fd = open(str, O_CREAT | O_WRONLY);
            dup2(fd, 1);
            for (int j = 0; mass[j] != NULL; j++) {
                if (strcmp(mass[j], "<") == 0) {
                    status_of_work = open_f(mass[j + 1], newmass, trig, list);
                }
            }
            dup2(save_fd, 1);
        }
    return status_of_work;
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
    return status_of_work;
}
