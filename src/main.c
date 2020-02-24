#include "../inc/ush.h"

// static void lsh_cd(char **args) {
//     if (chdir(args[1]) != 0) {
//         perror("u$h");
//     }
// }

int main(int argc, char **argv) {
    char *line;
    char **mass;

    if (argv && argc > 0)
        while (1) {
            printf("🔥 u$h> ");
            line = mx_read_line();
            mass = mx_strsplit(line);
        }
}
