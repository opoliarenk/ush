#include "../inc/ush.h"

static int built_done(char **mass, t_trig *trig, t_var **list) {
    int status_of_work = 1;

    if ((status_of_work = mx_red_pipe(mass, trig, list)) == 2) {
        mx_builtins(mass, trig, list);
        status_of_work = trig->err;
    } 
    return status_of_work;
}

static void subst(char ***mass, t_trig *trig, t_var **list, char *newl) {
    char **new = NULL;

    for (int i = 0; newl[i]; i++)
        if (newl[i] == '\\' && newl[i + 1] == '`')
            return ;
    if ((new = mx_sub(*mass, trig, list)) != NULL) {
        mx_del_strarr(mass);
        (*mass) = new;
    }
}

int mx_hardparser(char *line, t_trig *trig, t_var **list) {
    char *cuts = mx_cut_spaces(line);
    char *newl = mx_hardsplit(cuts);
    char **mass = NULL;
    int status_of_work = 1;
    
    mx_pre_substr(&newl);
    mass = mx_delim_space(newl);
    trig->linput = mx_strdup(cuts);
    mx_variable(mass, list);
    mx_v_out(mass, list);
    if (mx_mt(&mass) == 1) {
        free(cuts);
        free(newl);
        return status_of_work;
    }
    subst(&mass, trig, list, newl);
    status_of_work = built_done(mass, trig, list);
    free(newl);
    mx_del_strarr(&mass);
    free(cuts);
    free(trig->linput); 
    return status_of_work;
}
