#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    bool exibit = true;
    int i = 0;
    extern char **environ;
    
    while (exibit) {
        printf("u$h> ");
        line = mx_wait_line(); //mx_canon();
        if (line) {
            mass = mx_connectors(line);
            if (mass[0] != NULL) {
                if (strcmp(mass[0], "-1") == 0)
                    return 0;
                while(mass[i]) {
                    mx_logic(mass[i]);
                    i++;
                }
            }
            for (int i = 0; mass[i]; i++) {
                if (strcmp(mass[i], "exit") == 0)
                    exibit = false;
                if (strcmp(mass[i], "env") == 0)
                    mx_builtin_env(environ);
                if (strcmp(mass[i], "export") == 0)
                    mx_builtin_export(mass[i + 1], mass[i + 2], environ);
                if (strcmp(mass[i], "cd") == 0)
                    mx_builtin_cd(mass[i + 1]);
                if (strcmp(mass[i], "pwd") == 0)
                    mx_builtin_pwd();
                if (strcmp(mass[i], "echo") == 0)
                   mx_builtin_echo(mass[i + 1]);
                //if (strcmp(mass[i], "unset") == 0)
                //    mx_builtin_unset();
                //if (strcmp(mass[i], "which") == 0)
                //    mx_builtin_which();
                //if (strcmp(mass[i], "fg") == 0)
                //    mx_builtin_fg();
            }

        }
        
    }
    return 0;
}
