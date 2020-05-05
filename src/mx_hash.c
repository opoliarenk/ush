#include "../inc/ush.h"

static void while_str(int *i, char *line) {
    (*i)++;
    while (line[(*i)] != '\"' && line[(*i) - 1] != '\\')
        (*i)++;    
}

static void while_not(int *i, char *line) {
    (*i)++;
    while (line[(*i)] != '\'')
        (*i)++;
}

static char *creat_dup(int flag, char *new, char *line, int i) {
    if (flag == 1) {
        new = strndup(line, i - 1);
        return new;
    } 
    return NULL;
}

char *mx_hash (char *line) { 
    int i = 0;
    int flag = 0;
    char *new = NULL;
    
    for (; i < mx_strlen(line); i++) {
        if (i == 0 && line[i] == '\"')
            while_str(&i, line);
        else if (line[i] == '\"' && i == 0) 
            while_str(&i, line);
        else if (line[i] == '\'' && i == 0)
            while_not(&i, line);
        else if (line[i] == '\'' && line[i - 1] != '\\')
            while_not(&i, line);
        else if (line[i] == '#') {
            flag = 1;
            break;
        }
    }
    return creat_dup(flag, new, line, i);
}
