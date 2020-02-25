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

    while (1) {
        printf("u$h> ");
        line = mx_wait_line();
        mass = mx_strsplit(line);
        char *arr[4] = {"/bin/ls", "-l", "src", NULL};
        if (strcmp(mass[0], "ls") == 0) {
            free(mass[0]);
            mass[0] = strdup("/bin/ls");
            execve(mass[0], arr, environ);
        }
    }
    return 0;
}
