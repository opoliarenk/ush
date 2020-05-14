#include "../inc/ush.h"

static void sub(char ***news, char **mass, char *str, char **buff_mass) {
    int i = 0;
    int j = 0;
    int h = 0;

    while (mass[i] != NULL) {
        if (strcmp(mass[i], str) != 0) {
            (*news)[h] = strdup(mass[i]);
            h++;
            i++;
        } 
        else {
            while (buff_mass[j] != NULL) {
                (*news)[h] = strdup(buff_mass[j]);
                h++;
                j++;
            }
            i++;
        }
    }
    (*news)[h] = NULL;
}

char **mx_end_sub(char **mass, char *str) { 
    char **buff_mass = NULL;
    char **news = NULL;
    int i = 0;
    int j = 0;

    buff_mass = mx_delim_space(str);
    while (buff_mass[j++] != NULL);
    while (mass[i++] != NULL);
    i--;
    news = (char **)malloc(sizeof(char *) * (j + i) + 1);
    sub(&news, mass, str, buff_mass);
    mx_del_strarr(&buff_mass);
    return news;
}
