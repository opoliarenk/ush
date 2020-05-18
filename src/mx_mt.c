#include "../inc/ush.h"

int mx_mt(char ***mass) {
    char *str = NULL;

    for (int i = 0; (*mass)[i]; i++) {
        if ((*mass)[i][0] == '\'' || (*mass)[i][0] == '\"')
            continue;
        if ((str = mx_tilde(&(*mass)[i])) == NULL) {
            mx_del_strarr(mass);
            return 1;
        }
        else {
            free((*mass)[i]); 
            (*mass)[i] = strdup(str);
            free(str);
        }
    }
    return 0;
}
