#include "../inc/ush.h"

static int built_done(char **mass, t_trig *trig, t_var **list) {
    int status_of_work = 1;

    if ((status_of_work = mx_red_pipe(mass, trig, list)) == 2) {
        mx_builtins(mass, trig, list);
        status_of_work = trig->err;
    } 
    return status_of_work;
}

static void subst(char ***mass, t_trig *trig, t_var **list) {
    char **new = NULL;

    if ((new = mx_sub(*mass, trig, list)) != NULL) {
        mx_del_strarr(mass);
        (*mass) = new;
    }
}

int mx_hardparser(char *line, t_trig *trig, t_var **list) {
    char *cuts = mx_cut_spaces(line);
    char *newl = mx_hardsplit(cuts);
    char **mass = mx_delim_space(newl);
    int status_of_work = 1;

    if (mx_mt(&mass) == 1)
        return status_of_work;
    trig->linput = mx_strdup(cuts);
    mx_variable(mass, list);
    mx_v_out(mass, list);
    subst(&mass, trig, list);
    status_of_work = built_done(mass, trig, list);
    //                mx_printstr("-------------\n");
    // int i = 0;
    // while (mass[i]) {
    //     mx_printstr(mass[i]);
    //     mx_printchar('\n');
    //     i++;
    // }
    // mx_printstr("-------------\n");
    free(newl);
    //mx_del_strarr(&mass);
    free(cuts);
    return status_of_work; 
}
