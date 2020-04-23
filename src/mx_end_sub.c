#include "../inc/ush.h"

char **mx_end_sub(char **mass, char *str) { //mass[i] == str
    char **buff_mass = NULL;
    char **news = NULL;
    int i = 0;
    int j = 0;
    int h = 0;

    buff_mass = mx_delim_space(str);
    while (buff_mass[j++] != NULL);
    while (mass[i++] != NULL);
    i--;
    news = (char **)malloc(sizeof(char *) * (j + i) + 1);
    i = 0;
    j = 0;
    while (mass[i] != NULL) {
        if (strcmp(mass[i], str) != 0) {
            news[h] = strdup(mass[i]);
            h++;
            i++;
        } 
        else {
            while (buff_mass[j] != NULL) {
                news[h] = strdup(buff_mass[j]);
                h++;
                j++;
            }
            i++;
        }
    }
    news[h] = NULL;
    return news;
}
