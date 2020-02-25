#include "../inc/ush.h"

void mx_fork(char **mass) {
    pid_t pid;

    if (strcmp(mass[0], "cd") == 0) {
        pid = fork();
        if (chdir(mass[1]) != 0) {
            perror("u$h");
        }
        printf("%d\n", pid);
    }
}
