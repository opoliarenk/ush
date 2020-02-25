#include "../inc/ush.h"

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
        // if (mass != NULL)
        //     mx_fork(mass);
    }
    return 0;
}
