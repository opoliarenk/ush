#include "../inc/ush.h"

static void env_creat(char **new, char **env, t_trig *trig) {
    extern char **environ;
    int i = 0;

    setenv("PATH", new[0], 1);
    if (new[1] != NULL)
        mx_env_not(&new[1], trig, environ);
    else {
        while(env[i]) {
            mx_printstr(env[i++]);
            mx_printchar('\n');
        }
    }
    exit(trig->err);
}

static void some_help() {
    mx_printerr("env: option requires an argument -- P\n");
    mx_printerr("usage: env [-i] [-P utilpath] [-u name]\n");
	mx_printerr("           ");//11probelov
	mx_printerr("[name=value ...] [utility [argument ...]]\n");
}

void mx_env_P(char **mass, t_trig *trig, char **environ) {
    char **new = mx_mallocing_new(mass);
    pid_t pid;
    int status;

    if (new[0] != NULL) {
        pid = fork();
        if (pid == 0) 
           env_creat(new, environ, trig);
        else {
            waitpid(pid, &status, WUNTRACED);
            trig->err = status;
            mx_del_strarr(&new);
        }
    }
    else 
        some_help();
}
