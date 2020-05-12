#include "../inc/ush.h"

static void helper(char **new, char ***env_n, t_trig *trig) {
    int count = 0;

    for (int i = 0; new[i]; i++) {
        if (strstr(new[i], "=") != NULL) {
            (*env_n)[count] = strdup(new[i]);
            count++;
        } 
        else 
            break;
    }
    mx_env_not(&new[count], trig, (*env_n));
}

static char **creat_env(char **new) {
    int count = 0;
    char **env_n = NULL;

    for (int i = 0; new[i]; i++) 
        if (mx_count_substr(new[i], "=") == 1)
            count++;
    env_n = (char**) malloc( sizeof(char*) * count + 1);
    env_n[count] = NULL;
    return env_n;
}

void mx_env_i(char **mass, t_trig *trig) {
    char **new = mx_mallocing_new(mass);
    char **env_n = NULL;

    if (new[0] != NULL) {
        env_n = creat_env(new);
        helper(new, &env_n, trig);
        mx_del_strarr(&new);
        //if (env_n[0] != NULL)
            mx_del_strarr(&env_n);
    }
}

