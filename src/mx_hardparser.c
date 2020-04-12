#include "../inc/ush.h"

int mx_hardparser(char *line, t_trig *trig, t_var **list) {
    char *cuts = mx_cut_spaces(line);
    char *newl = mx_hardsplit(cuts); //FREE
    // тут надо будет поставить проверку на переменные 
    char **mass = mx_delim_space(newl); //FREE
    int status_of_work = 1;

    mx_variable(mass, list);
    int i = 0;
    while (mass[i] != NULL) {
        if (strcmp(mass[i], "$") == 0) {
            if (list != NULL) {
            while((*list)->next != NULL) {
                if (strcmp(mass[i + 1], (*list)->name_of_data) == 0) {
                    mx_printstr((*list)->data);
                }
                (*list) = (*list)->next;
            }
            }
        }
        //mx_printstr(mass[i]);
        //mx_printchar('\n');
        i++;
    } //nado budet ubrat
    
    if ((status_of_work = mx_red_pipe(mass, trig)) == 2) {
        mx_builtins(mass, trig);
        status_of_work = trig->err;
    }
    free(newl);
    //mx_del_strarr(&mass);
    return status_of_work; // временно
}
