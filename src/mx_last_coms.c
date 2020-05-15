#include "../inc/ush.h"

void mx_last_coms(char **temp) {
    char *buff = mx_strnew(strlen((*temp)) - 2);
    int j = 0;

    for (int i = 1; i < mx_strlen((*temp)) - 1; i++) {
        buff[j] = (*temp)[i];
        j++;
    }
    free((*temp));
    (*temp) = strdup(buff);
    free(buff);
}
