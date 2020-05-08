#include "../inc/ush.h"

void mx_sub_counts(char **str, int *j_i_f) {
    if ((*str)[j_i_f[1]] == '$' && (*str)[j_i_f[1] + 1] == '(') 
        j_i_f[0]++;
    if ((*str)[j_i_f[1]] == '`' && j_i_f[2] == 0) { 
        j_i_f[0]++;
        j_i_f[2] = 1;
    }
    else if ((*str)[j_i_f[1]] == '`' && j_i_f[2] == 1) {
        j_i_f[2] = 0;
    }
}

