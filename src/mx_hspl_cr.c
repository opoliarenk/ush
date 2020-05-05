#include "../inc/ush.h"

void mx_hspl_cr(char *line, char **new, int *q, int *k) {
 if (line[(*k)] == '\"' && line[(*k) - 1] != '\\') {
        (*new)[(*q)++] = line[(*k)++];
        while (line[(*k)] != '\"') { 
            if (line[(*k)] == '\\') {
                (*new)[(*q)++] = line[(*k)++];
                (*new)[(*q)++] = line[(*k)++];
            } 
            else  {
                (*new)[(*q)++] = line[(*k)++];
            }
        }
    }
    else if (line[(*k)] == '\'' && line[(*k) - 1] != '\\') {
        (*new)[(*q)++] = line[(*k)++];
        while (line[(*k)] != '\'')
            (*new)[(*q)++] = line[(*k)++];
    }    
}

