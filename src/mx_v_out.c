#include "../inc/ush.h"

static void search_list(char *buff_n, t_var **list, char **temp) {
    t_var *buffl = *list;
    char *bn = mx_strjoin("$", buff_n);
    char *bt = NULL;
    char *envv = getenv(buff_n);

    if (envv != NULL) { //write functions 
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
}

static void var_replac(t_var **list, char **temp) {
    int len = strlen(*temp);
    char *buff_n = NULL;
    int j = 0;

    for (int i = 0; i < len; i++) {
        if ((*temp)[i] == '$') {
            i++;
            while ((*temp)[i] && ((*temp)[i] != ' ' && (*temp)[i] != '$' && (*temp)[i] != '\"')) { 
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
            while ((*temp)[i] && ((*temp)[i] != ' ' && (*temp)[i] != '$' && (*temp)[i] != '\"')) {
                buff_n[j] = (*temp)[i];
                j++;
                i++;
            }
            break;
        }
    }
    search_list(buff_n, list, temp);
}

void mx_v_out(char **mass, t_var **list) {    
    for (int i = 0; mass[i] != NULL; i++) {
        for (int j = 0; mass[i][j] != '\0'; j++) {
            if (mass[i][0] == '\'')
                break;
            if (mass[i][j] == '$') {
                var_replac(list, &mass[i]);
                break;
            }
        }
    }  
}
