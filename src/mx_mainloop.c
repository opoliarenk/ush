#include "../inc/ush.h"

static void auditor(char **mass, t_trig *trig, t_var *list) {
    int i = 0;

    if (mass && mass[0]) {
        while(mass[i]) {
            mx_logic(mass[i], trig, &list);
            i++;
        }
        i = 0;
    }
}

void mx_mainloop(t_trig *trig, t_var *list, t_input *input) {
    char *line;
    char **mass;
    struct termios tty;

    tcgetattr(0, &tty);
    while (trig->exit) {
        mx_canon_off();
        line = mx_input(input);
        dprintf(1, "\r\n");
        tcsetattr(0, TCSAFLUSH, &tty);
        if (line) {
            if (mx_check_echo(line)) {
                mass = mx_connectors(line);
                auditor(mass, trig, list);
                mx_del_strarr(&mass);
            }
            memset(line, '\0', strlen(line));
        }
    }
    mx_strdel(&line);
}
