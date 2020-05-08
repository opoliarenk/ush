#include "../inc/ush.h"

void mx_countingwh(char *line, int *i, int *kol) {
    (*i) += 2;
    (*kol)++;
    while ((*kol) != 0) {
        if (line[(*i)] == '\\') {
            (*i) += 2;
        }
        else if (line[(*i)] == '$' && line[(*i) + 1] == '(') {
            (*kol)++;
            (*i) += 2;
        }
        else {
            (*i)++;
        }
        if (line[(*i)] == ')')
            (*kol)--;
    }
}
