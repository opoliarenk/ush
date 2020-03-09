#include "../inc/ush.h"

void mx_builtins(char **arr, t_trig *trig) {
    extern char **environ;

    if (strcmp(arr[0], "exit") == 0) {
        trig->exit = 0;
        trig->err = mx_atoi(arr[1]);
    }
    if (strcmp(arr[0], "env") == 0)
        mx_builtin_env(environ);
    if (strcmp(arr[0], "export") == 0)
        mx_builtin_export(arr[1], arr[2], environ);
    if (strcmp(arr[0], "cd") == 0)
        mx_builtin_cd(arr, trig);
    if (strcmp(arr[0], "pwd") == 0)
        mx_builtin_pwd();
    if (strcmp(arr[0], "echo") == 0)
       mx_builtin_echo(arr);
    if (strcmp(arr[0], "unset") == 0)
        mx_builtin_unset(arr[1]);
    // if (strcmp(arr[0], "which") == 0)
    //    mx_builtin_which();
    // if (strcmp(arr[0], "fg") == 0)
    //    mx_builtin_fg();
}










































































