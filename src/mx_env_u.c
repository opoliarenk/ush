#include "../inc/ush.h"

static char **creating(char **environ, char **new) {
    int count = 0;
    char **env_n = NULL;

    for (int i = 0; environ[i]; i++)
        if (strstr(environ[i], new[0]) == NULL)
            count++;
    env_n = (char**)malloc(sizeof(char*) * count + 1);
    env_n[count] = NULL;
    count = 0;
    for (int i = 0; environ[i]; i++) {
        if (strstr(environ[i], new[0]) == NULL) {
            env_n[count] = strdup(environ[i]);
            count++;
        }
    }
    return env_n;
}

static void printerr_usage() {
    mx_printerr("env: option requires an argument -- u\n");
	mx_printerr("usage: env [-i] [-P utilpath] [-u name]\n");
	mx_printerr("           ");//11probelov
	mx_printerr("[name=value ...] [utility [argument ...]]\n");
}

void mx_env_u(char **mass, t_trig *trig, char **environ) {
    char **new = mx_mallocing_new(mass);
    char **env_n = NULL;

    if (new[0] != NULL) {
        env_n = creating(environ, new);
        if (new[1] != NULL)
            mx_env_not(&new[1], trig, env_n);
        else {
            for (int i = 0; env_n[i]; i++) {
                mx_printstr(env_n[i]);
                mx_printchar('\n');
            }
        }
        mx_del_strarr(&env_n);
        mx_del_strarr(&new);
    }
    else
        printerr_usage();
}
