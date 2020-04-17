#include "../inc/ush.h"

void mx_check_input(t_trig *trig, t_var *list) {
    char *buff = NULL;
    char **mass;
    size_t linecap = 0;
    ssize_t linelen = 0;
    int i = 0;

    if (!isatty(STDIN_FILENO)) {
        buff = mx_strnew(ARG_MAX + 1);
        while ((linelen = getline(&buff, &linecap, stdin)) > 0) {
            buff[linelen] = '\0';
            if (buff[linelen - 1] == '\n')
                buff[linelen - 1] = '\0';
            if (mx_check_echo(buff)) {
                mass = mx_connectors(buff);
                if (mass && mass[0]) {
                    while(mass[i]) {
                        mx_logic(mass[i], trig, &list);
                        i++;
                    }
                    i = 0;
                }
            }
            exit(trig->err);
        }
    }
}
