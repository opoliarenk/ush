#include "../inc/ush.h"

int mx_mt(char ***mass) {
    char *str = NULL;
    char *temp = NULL;

    for (int i = 0; (*mass)[i]; i++) {
        if ((*mass)[i][0] == '\'' || (*mass)[i][0] == '\"')
            continue;
        if ((str = mx_tilde((*mass)[i])) == NULL) {
            mx_del_strarr(mass);
            return 1;
        }
        else {
            temp = strdup(str);
            free((*mass)[i]);
            (*mass)[i] = strdup(temp);
            free(str);
            free(temp);
        }
    }
    return 0;
}
