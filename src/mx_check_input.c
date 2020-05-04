#include "../inc/ush.h"

static void help_d(char **mass, t_trig *trig, t_var *list) {
    int i = 0;

    if (mass && mass[0]) {
        while(mass[i]) {
            mx_logic(mass[i], trig, &list);
            i++;
        }
    }
}

static void all_free(char **mass, char *buff) {
    mx_del_strarr(&mass);
    mx_strdel(&buff);
}

void mx_check_input(t_trig *trig, t_var *list) {
    char *buff = NULL;
    char **mass = NULL;
    size_t linecap = 0;
    ssize_t lenght = 0;

    if (!isatty(STDIN_FILENO)) {
        buff = mx_strnew(ARG_MAX + 1);
        while ((lenght = getline(&buff, &linecap, stdin)) > 0) {
            buff[lenght] = '\0';
            if (buff[lenght - 1] == '\n')
                buff[lenght - 1] = '\0';
            if (mx_check_echo(buff)) {
                mass = mx_connectors(buff);
                help_d(mass, trig, list);
            }
            exit(trig->err);
        }
        all_free(mass, buff);
    }
}
