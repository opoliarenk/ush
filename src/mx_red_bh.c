#include "../inc/ush.h"

int mx_red_bh(char **mass, int i, char *str, int *fd) {
    int save_fd = dup(1);
    
    close(1);
    if (strcmp(mass[i + 1], ">") == 0)
        (*fd) = open(str, O_CREAT | O_APPEND | O_WRONLY);
    else 
        (*fd) = open(str, O_WRONLY | O_TRUNC);
    if ((*fd) == -1)
        (*fd) = open(str, O_CREAT | O_WRONLY);
    dup2((*fd), 1);
    return save_fd;
}
