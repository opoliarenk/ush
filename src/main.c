#include "../inc/ush.h"
#define _GNU_SOURCE

// static void lsh_cd(char **args) {
//     if (chdir(args[1]) != 0) {
//         perror("u$h");
//     }
// }

int main() {
    char *line;
    char **mass;
    extern char **environ;
    int status;

    while (1) {
        printf("u$h> ");
        line = mx_wait_line();
        mass = mx_strsplit(line);

        if (mass[0] != NULL) {
            if (strcmp(mass[0], "ls") == 0) {
                char *arr[4] = {"/bin/ls", mass[1], mass[2], NULL};
                pid_t pid;

                pid = fork();
                if (pid == 0) {
                    free(mass[0]);
                    mass[0] = strdup("/bin/ls");
                    execve(mass[0], arr, environ);
                } else 
                    while(pid != wait(&status));
            }
        }
        
    }
    return 0;
}
