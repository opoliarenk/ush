#include "../inc/ush.h"

void mx_var_rep_crt(char **temp, char **buff_n) {
    int len = strlen(*temp);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if ((*temp)[i] == '$') {
            i++;
            if ((*temp)[i] == '{') 
                i++;
            while ((*temp)[i] && ((*temp)[i] != ' ' 
                && (*temp)[i] != '$' && (*temp)[i] != '`' 
                && (*temp)[i] != ')' && (*temp)[i] != '\"' 
                && (*temp)[i] != '}')) {
                (*buff_n)[j] = (*temp)[i];
                j++;
                i++;
            }
            break;
        }
    }   
}

