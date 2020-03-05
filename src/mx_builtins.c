#include "../inc/ush.h"

void mx_builtins(char **arr, t_trig *trig) {
    extern char **environ;

	for (int i = 0; arr[i]; i++) {
        if (strcmp(arr[i], "exit") == 0) {
            trig->exit = 0;
            trig->err = mx_atoi(arr[i + 1]);
        }
        if (strcmp(arr[i], "env") == 0)
            mx_builtin_env(environ);
        if (strcmp(arr[i], "export") == 0)
            mx_builtin_export(arr[i + 1], arr[i + 2], environ);
        if (strcmp(arr[i], "cd") == 0)
            mx_builtin_cd(arr, trig);
        if (strcmp(arr[i], "pwd") == 0)
            mx_builtin_pwd();
        if (strcmp(arr[i], "echo") == 0)
           mx_builtin_echo(arr);
        if (strcmp(arr[i], "unset") == 0)
            mx_builtin_unset(arr[i + 1]);
        // if (strcmp(arr[i], "which") == 0)
        //    mx_builtin_which();
        // if (strcmp(arr[i], "fg") == 0)
        //    mx_builtin_fg();
    }
}
