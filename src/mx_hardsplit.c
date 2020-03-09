#include "../inc/ush.h"

char *mx_hardsplit(char *line) {
    int i;
    int j = 0;
    char *new = NULL;
    int k = 0;
    int flag = 0;
    
    for (i = 0; line[i] != '\0'; i++) {
        if ((line[i] == '\"' || line[i] == '\'') && line[i - 1] != '\\') {
            if (flag == 0)
                flag = 1;
            else 
                flag = 0;
        }
        if ((line[i] == '>' || line[i] == '\''  
        || line[i] == '$' || line[i] == '(' || line[i] == ')' 
        || line[i] == '{' || line[i] == '}' || line[i] == '`') && flag != 1)  
            j += 2;
    }
    i = i + j;
    flag = 0;
    new = mx_strnew(i);
    for (int q = 0; q <= i; q++) {
        if ((line[k] == '\"' || line[k] == '\'') && line[k - 1] != '\\') {
            if (flag == 0)
                flag = 1;
            else 
                flag = 0;
        }
        if ((line[k] == '>' || line[k] == '\''  
        || line[k] == '$' || line[k] == '(' || line[k] == ')' 
        || line[k] == '{' || line[k] == '}' || line[k] == '`') && flag != 1) {  
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
