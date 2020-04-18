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

int mx_redirout(char **mass, t_trig *trig, t_var **list) {
    char **newmass = newfor_bults(mass);
    int status_of_work = 2;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], "<") == 0) {
            status_of_work = open_f(mass[i + 1], newmass, trig, list);
        }
    }
    return status_of_work;
}
