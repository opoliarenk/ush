#include "../inc/ush.h"

static void helper1(char *line, int *i) {
    if (line[(*i)] == '\'' && line[(*i) - 1] != '\\') {
        (*i)++;
        while (line[(*i)] != '\'')
            (*i)++;
    } 
    else if (line[(*i)] == '\"' && line[(*i) - 1] != '\\') {
        (*i)++;
        while (line[(*i)] != '\"') {
            if (line[(*i)] == '\\')
                (*i) += 2;
            else 
                (*i)++;
        }
    }
}

static void helper2(char *line, int *i) {
    if (line[(*i)] == '\"') {
        (*i)++;
        while (line[(*i)] != '\"') {
            if (line[(*i)] == '\\')
                (*i) += 2;
            else 
                (*i)++;
        }
    }
    else if (line[(*i)] == '\'') {
        (*i)++;
        while(line[(*i)] != '\'')
            (*i)++;
    }
}

static void helper3(char *line, int *i, int *j) {
    if (line[(*i)] == '>' || line[(*i)] == '<')  
        (*j) += 2;
}

static void helper4(int *i, int *j) {
    (*j)+=2;
    (*i)++;
}

int mx_hspl_count(char *line) {
    int i = 0;
    int j = 0;

    for (i = 0; line[i] != '\0'; i++) {
        if (i != 0) {
            helper1(line, &i);
            if (line[i] == '2' && line[i + 1] == '>' && line[i - 1] == ' ') {
                helper4(&i, &j);
                continue;
            }
            helper3(line, &i, &j);
        } 
        else {
            helper2(line, &i);
            if (line[i] == '2' && line[i + 1] == '>') {
                helper4(&i, &j);
                continue;
            }
            helper3(line, &i, &j);
        }
    }
    return i + j;
}
