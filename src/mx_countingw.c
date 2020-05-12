#include "../inc/ush.h"

static void help_for_help1(char *line, int *i, int *kol) {
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

static void help_for_help2(char *line, int *i) {
    (*i)++;
    while (line[(*i)] != '`') {
        if (line[(*i)] == '\\')
            (*i) += 2;
        else 
            (*i)++;
    }
}

static void help1(char *line, int *i, int *kol) {
    if (line[(*i)] == '\\' && line[(*i) + 1] == ' ') {
        (*i) = (*i) + 2;
        if (line[(*i)] == '\0') {
            (*i)--;
            return ;
        }
    }
    if (line[(*i)] == '\"' && line[(*i) - 1] != '\\') {
        (*i)++;
        while (line[(*i)] != '\"') {
            if (line[(*i)] == '\\')
                (*i) += 2;
            else 
                (*i)++;
        }
    } 
    else if (line[(*i)] == '\'' && line[(*i) - 1] != '\\') {
        (*i)++;
        while (line[(*i)] != '\'')
            (*i)++;
    }
    else if (line[(*i)] == '`' && line[(*i) - 1] != '\\')
        help_for_help2(line, i);
    else if (line[(*i)] == '$' && line[(*i) + 1] == '(' && line[(*i) - 1] != '\\')
        help_for_help1(line, i, kol);
}

static void help2(char *line, int *i, int *kol) {
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
        while (line[(*i)] != '\'')
            (*i)++;
    } 
    else if (line[(*i)] == '`') 
        mx_countingwh1(line, i);
    else if (line[(*i)] == '$' && line[(*i) + 1] == '(') 
        mx_countingwh(line, i, kol);
}

int mx_countingw(char *line) {
    int len = strlen(line);
    int countw = 0;
    int kol = 0;

    for (int i = 0; i < len; i++) { 
        if (i != 0)
            help1(line, &i, &kol);
        else
            help2(line, &i, &kol);
        if (line[i] == ' ' || line[i] == '\t' 
            || line[i] == '\r' || line[i] == '\n' 
            || line[i] == '\a' || line[i + 1] == '\0') {
                while (line[i + 1] == ' ' || line[i + 1] == '\t' 
                    || line[i + 1] == '\r' || line[i + 1] == '\n' 
                    || line[i + 1] == '\a')
                        i++;
                countw++;
        }
    }
    return countw;
}
