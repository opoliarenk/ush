#include "../inc/ush.h"

static int is_one(char **temp) {
    int one = 0;

    for (int i = 0; (*temp)[i] != '\0'; i++) {
        if ((*temp)[i] == '$' && (*temp)[i + 1] == '{') {
            one = 0;
            break;
        } 
        else if ((*temp)[i] == '$' && (*temp)[i + 1] != '{') {
            one = 1; 
            break;
        }
    }  
    return one; 
}

static char *join_search(char *buff_n, char **temp) {
    int one = 0;
    char *tmp = NULL;
    char *bn = NULL;

    one = is_one(temp);
    if (one == 1) {
        bn = mx_strjoin("$", buff_n); 
    } 
    else {
        tmp = mx_strjoin("${", buff_n);
        bn = mx_strjoin(tmp, "}");
        free(tmp);
    }
    return bn;
}

static void search_list(char *buff_n, t_var **list, char **temp) {
    t_var *buffl = *list;
    char *bn = join_search(buff_n, temp);
    char *bt = NULL;
    char *envv = getenv(buff_n);
    int is_var = 0;

    if (envv != NULL) { 
        bt = mx_good_repl_var((*temp), bn, envv);
        free(*temp);
        *temp = bt;
        free(bn);
        return ;
    }
    while (buffl != NULL ) { 
        if (strcmp(buffl->name_of_data, buff_n) == 0) {
           bt = mx_good_repl_var((*temp), bn, buffl->data);
           free(*temp);
           *temp = bt;
           is_var = 1;
        }
        buffl = buffl->next;
    }
    if (is_var == 0)
        mx_no_var_is(bn, temp);
    free(bn);
}

static int var_replac(t_var **list, char **temp) {
    char *buff_n = NULL;
    int j = mx_var_rep_count(temp);

    buff_n = mx_strnew(j);
    mx_var_rep_crt(temp, &buff_n);
    search_list(buff_n, list, temp);
    free(buff_n); 
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
            if (mass[i][j] == '$' && mass[i][j + 1] != '(') {
                chang = var_replac(list, &mass[i]);
            }
        }
    }  
    mx_an_var(mass, chang, list);
}
