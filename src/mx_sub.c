#include "../inc/ush.h"

static void creat_pars(char **str, t_trig *trig, t_var **list) {
    int count = mx_count_substr(*str, "$(") + mx_count_substr(*str, "`") / 2;
    int j_i_f[3] = {0, 0, 0};

    for (; count > 0; count--) {
        for (j_i_f[1] = 0; (*str)[j_i_f[1]]; j_i_f[1]++) { 
            mx_sub_counts(str, j_i_f);
            if (j_i_f[0] == count) { 
                mx_workb1(str, trig, list, j_i_f);
                break;
            }
        }
    }
}

char **mx_sub(char **mass, t_trig *trig, t_var **list) {
    char **buff_mass = NULL;
    char **news = NULL;

    for (int i = 0; mass[i]; i++) {
        if ((strstr(mass[i], "$(") != NULL || strstr(mass[i], "`") != NULL) 
            && mass[i][0] != '\'') { 
            creat_pars(&mass[i], trig, list);
            news = mx_end_sub(mass, mass[i]);
            if ((buff_mass = mx_sub(news, trig, list)) == NULL) {
                return news;
            } 
            else {
                mx_del_strarr(&news);
                news = buff_mass;
            }
            break;
        }
    }
    return news;
}
