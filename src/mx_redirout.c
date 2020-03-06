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

static void open_f(char *line, char **mass, t_trig *trig) {
    int fd;
    char *str = NULL;
    int i = 0;
    char **newmass = NULL;
    int j = 0;
    
    fd = open(line, O_RDONLY);
    if (fd == -1) {
        perror("ush"); //ERROR
        return;
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
    mx_builtins(newmass, trig);
    //выполнять функу назара
}

int mx_redirout(char **mass, t_trig *trig) {
    char **newmass = newfor_bults(mass);

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], "<") == 0) {
            open_f(mass[i + 1], newmass, trig);
        }
    }
    return 0;
}
