#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    int i = 0;
    t_trig *trig = (t_trig *)malloc(sizeof(t_trig));
    t_input *input = malloc(sizeof(t_input)); //struct for input
    struct termios tty;
    tcgetattr(0, &tty);

    trig->exit = true;
    trig->err = 0;
    trig->last_cd = NULL;
    while (trig->exit) {
        mx_canon_off();
        line = mx_input(input); //input
        dprintf(1, "\r\n");
        tcsetattr(0, TCSAFLUSH, &tty);
        if (line) {
            mass = mx_connectors(line);
            if (mass[0]) {
                while(mass[i]) {
                    mx_logic(mass[i], trig);
                    i++;
                }
                i = 0;
            }
        }
    }
    return trig->err;
}
