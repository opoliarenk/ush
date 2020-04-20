#include "../inc/ush.h"

static char **parser(char **mass, t_trig *trig, t_var **list) {
    char **buff = NULL;
    int j = 0;
    int rememb;
    int save_fd = dup(1);

    close(1);
    
    int pipefd[2];
    pid_t pid;

    for (int i = 0; mass[i]; i++) {
        rememb = i;
        while (mass[i] && strcmp(mass[i], "|") != 0) {
            j++;
            i++;
        }
        buff = (char **) malloc(sizeof(char *) * j + 1);
        for (int h = 0; h < j; h++)
            buff[h] = strdup(mass[rememb++]);
        j = 0;

        pipe(pipefd);
        pid = fork();
        if (pid == 0) {
            close(pipefd[1]);
            


        }
    }

}

int mx_pipe(char **mass, t_trig *trig, t_var **list) {
    int status_of_work = 2;
    int count = 0;

    for (int i = 0; mass[i]; i++) {
        if (strcmp(mass[i], "|") == 0) {
            
        }
    }
    
}
