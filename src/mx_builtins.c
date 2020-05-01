#include "../inc/ush.h"

static void sigcatch(int sig) {
    mx_printstr("\nsig catch ");
    mx_printint(sig);
    mx_printchar(10);
}

void mx_builtins(char **arr, t_trig *trig, t_var **list) {
    extern char **environ;
    
    trig->err = 0;
    signal(SIGTSTP, sigcatch);
    signal(SIGINT, sigcatch);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    //signal(SIGSEGV, SIG_IGN);
    if (strcmp(arr[0], "exit") == 0) {
        trig->exit = 0;
        trig->err = mx_atoi(arr[1]);
    } else if (strcmp(arr[0], "env") == 0)
        mx_builtin_env(environ);
    else if (strcmp(arr[0], "export") == 0)
        mx_builtin_export(arr, environ, list);
    else if (strcmp(arr[0], "cd") == 0)
        mx_builtin_cd(arr, trig);
    else if (strcmp(arr[0], "pwd") == 0)
        mx_builtin_pwd(arr, trig);
    else if (strcmp(arr[0], "echo") == 0)
        mx_builtin_echo(arr, trig->linput);
    else if (strcmp(arr[0], "unset") == 0)
        mx_builtin_unset(arr, list);
    else if (strcmp(arr[0], "which") == 0)
        mx_builtin_which(arr, trig);
    else if (strcmp(arr[0], "fg") == 0)
        mx_builtin_fg(arr, trig);
    else if (strcmp(arr[0], "true") == 0)
        mx_builtin_true(trig);
    else if (strcmp(arr[0], "false") == 0)
        mx_builtin_false(trig);
    else
        mx_notbuiltin(arr, trig, environ);
}
