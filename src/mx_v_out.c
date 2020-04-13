#include "../inc/ush.h"

static void var_replac(t_var **list, char **str) {
    int len = strlen(*str);
    char *buff_n = NULL;
    // int len_name = 0;
    int j = 0;
    char *temp = *str;

    if (*list != NULL) {
       //
    }
    for (int i = 0; i < len; i++) {
        if (temp[i] == '$') {
            i++;
            if (temp[i]) {
                while (temp[i] != ' ' || temp[i] != '$') { //тут что-то не так
                    j++;
                    i++;
                }
            } 
            else {
                mx_printstr("NE SUSHEVST");
                exit(0);
            }
            
        }
    }
    buff_n = mx_strnew(j);
    j = 0;
    for (int i = 0; i < len; i++) {
        if (temp[i] == '$') {
            i++;
            while (temp[i] != ' ' || temp[i] != '$') {
                if (temp[i] == '\0')
                    break;
                buff_n[j] = temp[i];
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
