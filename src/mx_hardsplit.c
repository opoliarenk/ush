#include "../inc/ush.h"

char *mx_hardsplit(char *line) {
    int i;
    int j = 0;
    char *new = NULL;
    int k = 0;
    
    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == '>' || line[i] == '\''  
        || line[i] == '$' || line[i] == '(' || line[i] == ')' 
        || line[i] == '{' || line[i] == '}' || line[i] == '`') //|| line[i] == '\\' 
            j += 2;
    }
    i = i + j;
    new = mx_strnew(i);
    for (int q = 0; q <= i; q++) {
        if (line[k] == '>' || line[k] == '\''  
        || line[k] == '$' || line[k] == '(' || line[k] == ')' 
        || line[k] == '{' || line[k] == '}' || line[k] == '`') { //|| line[i] == '\\' 
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
    new[i] = '\0';
    return new;
}
