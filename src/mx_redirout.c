#include "../inc/ush.h"

static char *easy_split(char *line) {
    int i;
    int j = 0;
    char *new = NULL;
    int k = 0;
    
    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == '<') 
            j = j + 2;
    }
    i = i + j;
    new = mx_strnew(i);
    for (int q = 0; q < i; q++) {
        if (line[k] == '<') {
            new[q++] = ' ';
            new[q++] = line[k];
            new[q] = ' ';
            k++;
        } 
        else {
            new[q] = line[k];
            k++;
        }
    }
    return new;
}

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

static void open_f(char *line, char **mass) {
    int fd;
    char *str = NULL;
    int i = 0;
    char **newmass = NULL;
    
    fd = open(line, O_RDONLY);
    if (fd == -1) {
        perror("ush"); //ERROR
        return;
    }
    char *str = mx_file_to_str(line);
    while (mass[i]) {
        i++;
    } 
    newmass = malloc (sizeof (char *) * (i + 2));
    for (j = 0; j < i + 2; j++) {
        while (mass[j])
            newmass[j++] = strdup(mass[j]);
        newmass[j] = strdup(str);
    }
    newmass[i + 1] = NULL;
    
    //выполнять функу назара
    }
}

int mx_redirout(char *line) {
    char *newl = easy_split(line); //FREE
    char **mass = mx_sh_splite(newl); //FREE
    char **newmass = newfor_bults(mass);

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], "<") == 0) {
            open_f(mass[i + 1], newmass);
        }
    }
    return 0;
}
