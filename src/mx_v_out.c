#include "../inc/ush.h"

static char *join_search(char *buff_n, char **temp) {
    int one = 0;
    char *tmp = NULL;
    char *bn = NULL;

    for (int i = 0; (*temp)[i] != '\0'; i++) {
        if ((*temp)[i] == '$' && (*temp)[i + 1] == '{') {
            one = 0;
            break;
        } else if ((*temp)[i] == '$' && (*temp)[i + 1] != '{') {
            one = 1; 
            break;
        }
    }
    if (one == 1) {
        bn = mx_strjoin("$", buff_n); 
    } else {
        tmp = mx_strjoin("${", buff_n);
        bn = mx_strjoin(tmp, "}");
    }
    return bn;
}

static void search_list(char *buff_n, t_var **list, char **temp) {
    t_var *buffl = *list;
    char *bn = join_search(buff_n, temp);
    char *bt = NULL;
    char *envv = getenv(buff_n);

    if (envv != NULL) { //
        bt = mx_replace_substr(*temp, bn, envv);
        free(*temp);
        *temp = bt;
        return ;
    }
    while (buffl != NULL ) { // check leaks
        if (strcmp(buffl->name_of_data, buff_n) == 0) {
           bt = mx_replace_substr(*temp, bn, buffl->data);
           free(*temp);
           *temp = bt;
        }
        buffl = buffl->next;
    }
    free(bn);
}

static int var_replac(t_var **list, char **temp) {
    int len = strlen(*temp);
    char *buff_n = NULL;
    int j = 0;

    for (int i = 0; i < len; i++) {
        if ((*temp)[i] == '$') {
            i++;
            if ((*temp)[i] == '{') //ubrat esli chto
                i++;
            while ((*temp)[i] && ((*temp)[i] != ' ' && (*temp)[i] != '$' && (*temp)[i] != '\"' && (*temp)[i] != '}')) { 
                j++;
                i++;
            }
            break;
        }
    }
    buff_n = mx_strnew(j);
    j = 0;
    for (int i = 0; i < len; i++) {
        if ((*temp)[i] == '$') {
            i++;
            if ((*temp)[i] == '{') //ubrat esli chto
                i++;
            while ((*temp)[i] && ((*temp)[i] != ' ' && (*temp)[i] != '$' && (*temp)[i] != '\"' && (*temp)[i] != '}')) {
                buff_n[j] = (*temp)[i];
                j++;
                i++;
            }
            break;
        }
    }
    search_list(buff_n, list, temp);
    return 0;
}

void mx_v_out(char **mass, t_var **list) {    
    int chang = 1;

    for (int i = 0; mass[i] != NULL; i++) {
        for (int j = 0; mass[i][j] != '\0'; j++) {
            if (mass[i][j] == '\'') {
                j++;
                while (mass[i][j] && mass[i][j] != '\'') {
                    j++;
                }
            }
            if (mass[i][j] == '$') {
                chang = var_replac(list, &mass[i]);
                //break;
            }
        }
    }  
    for (int i = 0; mass[i] != NULL; i++) {
        for (int j = 0; mass[i][j] != '\0'; j++) {
            if (mass[i][j] == '\'')
                break;
            if (mass[i][j] == '\"')
                break;
            if (chang == 0 && mass[i][j] == '=' && mass[i][j + 1] != '\'') {
                mx_variable(mass, list);
                break;
            }

        }
    }
}
