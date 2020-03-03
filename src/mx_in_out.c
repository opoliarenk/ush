#include "../inc/ush.h"

static char *easy_split(char *line) {
    int i;
    int j = 0;
    char *new = NULL;
    int k = 0;
    
    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == '<' || line[i] == '>') 
            j = j + 2;
    }
    i = i + j;
    new = mx_strnew(i);
    for (int q = 0; q < i; q++) {
        if (line[k] == '<' || line[i] == '>') {
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

void mx_in_out(char *line) {
    char *newl = easy_split(line); //FREE
    char **mass = mx_sh_splite(newl); //FREE
    char **newmass = NULL;

    for (int i = 0; mass[i] != NULL; i++) {
        
    }
}
