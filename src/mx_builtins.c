#include "../inc/ush.h"

static void making_err(t_trig *trig, t_var **list) { //$?
    t_var *newl = *list;
    char *it = mx_itoa(trig->err);

    while (newl) {
        if (strcmp(newl->name_of_data, "?") == 0) {
            free(newl->data);
            newl->data = strdup(it);
            break;
        }
        newl = newl->next;
    }
    free(it);
}

static bool part1(char **arr, t_trig *trig, t_var **list, char **environ) {
    if (strcmp(arr[0], "exit") == 0)
        mx_builtin_exit(arr, trig); 
    else if (strcmp(arr[0], "env") == 0)
        mx_builtin_env(environ, arr, trig);
    else if (strcmp(arr[0], "export") == 0)
        mx_builtin_export(arr, environ, list);
    else if (strcmp(arr[0], "cd") == 0)
        mx_builtin_cd(arr, trig);
    else if (strcmp(arr[0], "pwd") == 0)
        mx_builtin_pwd(arr, trig);
    else if (strcmp(arr[0], "echo") == 0)
        mx_builtin_echo(arr, trig->linput);
    else
        return false;
    return true;
}

static bool part2(char **arr, t_trig *trig, t_var **list) {
    if (strcmp(arr[0], "unset") == 0)
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
        return false;
    return true;
}

void mx_builtins(char **arr, t_trig *trig, t_var **list) {
    extern char **environ;
    
    trig->err = 0;
    mx_signals();
    if (!part1(arr, trig, list, environ) && !part2(arr, trig, list))
        mx_notbuiltin(arr, trig, environ);
    making_err(trig, list);
}

