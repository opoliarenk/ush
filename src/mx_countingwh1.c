#include "../inc/ush.h"

void mx_countingwh1(char *line, int *i) {
    (*i)++;
    while (line[(*i)] != '`') {
        if (line[(*i)] == '\\')
            (*i) += 2;
        else 
        (*i)++;
    }
}
