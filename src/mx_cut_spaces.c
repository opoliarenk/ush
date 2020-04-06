#include "../inc/ush.h"

static char *creating(int kol, char *line) {
    char *new = mx_strnew(strlen(line) - kol);
    int i = 0;
    int j = strlen(line) - 1;
    int cons = 0;
    
    while (line[i] == ' ' || line[i] == '\t' 
            || line[i] == '\r' || line[i] == '\n' 
            || line[i] == '\a')
                i++;
    cons = i;
    while (line[j] == ' ' || line[j] == '\t' 
            || line[j] == '\r' || line[j] == '\n' 
            || line[j] == '\a') 
                j--;
    for (int h = 0; h + cons <= j; h++) {
        new[h] = line[i];
        i++;
    }
    return new;
}

char *mx_cut_spaces(char *line) {
    int i = 0;
    int j = strlen(line) - 1;

    while (line[i] == ' ' || line[i] == '\t' 
            || line[i] == '\r' || line[i] == '\n' 
            || line[i] == '\a')
                i++;
    while (line[j] == ' ' || line[j] == '\t' 
            || line[j] == '\r' || line[j] == '\n' 
            || line[j] == '\a') {
                i++;
                j--;
    }
    return creating(i, line);
}
