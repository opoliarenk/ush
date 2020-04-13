#include "../inc/ush.h"

static void var_replac(t_var **list, char **str) {
    int len = strlen(*str);
    char *buff_n = NULL;
    int j = 0;

    if (*list != NULL) {
       //
    }
    for (int i = 0; i < len; i++) {
        if (*str[i] == '$') {
            i++;
            while (*str[i] && (*str[i] != ' ' || *str[i] != '$')) { 
                j++;
                i++;
            }
        }
    }
    buff_n = mx_strnew(j);
    j = 0;
    for (int i = 0; i < len; i++) {
        if (*str[i] == '$') {
            i++;
            while (*str[i] && (*str[i] != ' ' || *str[i] != '$')) {
                buff_n[j] = *str[i];
                j++;
                i++;
            }
        }
    }
    mx_printstr(buff_n);

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
