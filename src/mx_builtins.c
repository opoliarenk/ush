#include "../inc/ush.h"

static void sigcatch(int sig) {
    mx_printstr("\nsig catch ");
    mx_printint(sig);
    mx_printchar(10);
}

static void making_err(t_trig *trig, t_var **list) { //$?
    t_var *newl = *list;
    while (newl) {
        if (strcmp(newl->name_of_data, "?") == 0) {
            free(newl->data);
            newl->data = strdup(mx_itoa(trig->err));
            break;
        }
        newl = newl->next;
    }
}

void mx_builtins(char **arr, t_trig *trig, t_var **list) {
    extern char **environ;
    
    trig->err = 0;
    signal(SIGTSTP, sigcatch);
    signal(SIGINT, sigcatch);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGSEGV, sigcatch);
    if (strcmp(arr[0], "exit") == 0)
        mx_builtin_exit(arr, trig); 
    else if (strcmp(arr[0], "env") == 0)
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
    making_err(trig, list);
}
