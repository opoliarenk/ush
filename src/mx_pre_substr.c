#include "../inc/ush.h"

static void repl_sub_las(char *newl) {
    
    for (int i = strlen(newl); i >= 0; i--) {
        if (newl[i] == '`' && newl[i - 1] != '\\') {
            i--;
            while (newl[i] != '`' && newl[i - 1] != '\\')
                i++;
            newl[i] = ')';
            newl[i - 1] = 127;
            break;
        }
    }
}

static void repl_sub_fir(char *newl) {
    int temp = 1;

    for (int i = 0; newl[i]; i++) {
        if (newl[i] != '\\' && newl[i + 1] == '`' && temp != 0) {
            i = i + 2;
            while (newl[i] != '`') {
                if (newl[i] == '\\' && newl[i + 1] == '`') {
                    newl[i] = '$';
                    newl[i + 1] = '(';
                    temp = 0;
                    break;
                }
                i++;
            }
        }
    }
    repl_sub_las(newl);
}

static char *new(char *newl) {
    char *nn = mx_strnew(strlen(newl - 1));
    int j = 0;

    for (int i = 0; newl[i]; i++) {
        if (newl[i] != 127) {
            nn[j] = newl[i];
            j++;
        }
    }
    return nn;
}

static void count_of(char **newl, int *count, int *i) {
    (*i) = (*i) + 2;
    while ((*newl)[(*i)] != '`' && (*newl)[*i] != '\0') {
        if ((*newl)[(*i)] == '\\' && (*newl)[(*i) + 1] == '`') {
            (*count)++;
            (*i)++;
        }
        (*i)++;
    }
}
 
void mx_pre_substr(char **newl) {
    int count = 0;
    char *temp = NULL;

    for (int i = 0; (*newl)[i]; i++) {
        if ((*newl)[i] != '\\' && (*newl)[i + 1] == '`' && (*newl)[i + 2] != '\0') {
            count_of(newl, &count, &i);
            if (count % 2 == 0 && count != 0) {
                repl_sub_fir((*newl));
                temp = new((*newl));
                free((*newl));
                (*newl) = mx_strdup(temp);
                free(temp);
                break;
            }
            i--;
        }
    }
}
