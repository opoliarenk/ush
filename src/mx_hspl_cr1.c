#include "../inc/ush.h"

void mx_hspl_cr1(char *line, char **new, int *k, int *q) {
    if (line[(*k)] == '\"') {
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
    else if (line[(*k)] == '\'') {
        (*new)[(*q)++] = line[(*k)++];
        while (line[(*k)] != '\'')
            (*new)[(*q)++] = line[(*k)++];
    }
}
