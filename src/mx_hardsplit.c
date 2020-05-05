#include "../inc/ush.h"

static void error_cut(char **new, int *q, int *k) {
    (*new)[(*q)++] = ' ';
    (*new)[(*q)++] = '2';
    (*new)[(*q)++] = '>';
    (*new)[(*q)] = ' ';
    (*k) = (*k) + 2;
}

static void old_one(char *line, char **new, int *k, int *q) {
    if (line[(*k)] == '>' || line[(*k)] == '<') {  
        (*new)[(*q)++] = ' ';
        (*new)[(*q)++] = line[(*k)];
        (*new)[(*q)] = ' ';
        (*k)++;
    } 
    else {
        (*new)[(*q)] = line[(*k)];
        (*k)++;
    }
}

static void cycle(char *line, char **new, int i) {
    int k = 0;

    for (int q = 0; q < i; q++) {
        if (k != 0) {
            mx_hspl_cr(line, new, &q, &k);
            if (line[k] == '2' && line[k + 1] == '>' && line[k - 1] == ' ') {
                error_cut(new, &q, &k);
                continue;
            }     
        } 
        else {
            mx_hspl_cr(line, new, &k, &q);
            if (line[k] == '2' && line[k + 1] == '>' && line[k - 1] == ' ') {
                error_cut(new, &q, &k);
                continue;
            }     
        }
        old_one(line, new, &k, &q);
    }
    (*new)[i] = '\0';
}

char *mx_hardsplit(char *line) {
    int i;
    char *new = NULL;
    char *newww = mx_hash(line);
    
    if ( newww != NULL) {
        line = mx_strdup(newww);
        free(newww);
    }
    i = mx_hspl_count(line);
    new = mx_strnew(i);
    cycle(line, &new, i);
    return new;
}
