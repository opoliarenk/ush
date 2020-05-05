#include "../inc/ush.h"

void mx_del_4_echo(char **split, t_echo **echo) {
    mx_del_strarr(&split);
    free(*echo);
    (*echo) = NULL;
}
