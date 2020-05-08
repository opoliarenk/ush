#include "../inc/ush.h"

int mx_var_rep_count(char **temp) {
    int j = 0;
    int len = strlen(*temp);

    for (int i = 0; i < len; i++) {
        if ((*temp)[i] == '$') {
            i++;
            if ((*temp)[i] == '{') 
                i++;
            while ((*temp)[i] && ((*temp)[i] != ' ' 
                && (*temp)[i] != '$' && (*temp)[i] != '`' 
                && (*temp)[i] != ')' && (*temp)[i] != '\"' 
                && (*temp)[i] != '}')) { 
                j++;
                i++;
            }
            break;
        }
    }
    return j;
}
