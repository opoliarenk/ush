#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    int i = 0;
    t_trig *trig = (t_trig *)malloc(sizeof(t_trig));
    //lena
    t_input *input = malloc(sizeof(t_input)); //struct for input
    input->history_head = (t_history_list *)malloc(sizeof(t_history_list));
    struct termios tty;
    tcgetattr(0, &tty);
    //lena

    trig->exit = true;
    trig->err = 0;
    trig->PWD = (char *)malloc(50 * sizeof(char));
    trig->OLDPWD = (char *)malloc(50 * sizeof(char));
    trig->OLDPWD = getenv("HOME");
    trig->PWD = getenv("HOME");
    while (trig->exit) {
        //lena
        mx_canon_off();
        line = mx_input(input); //input
        dprintf(1, "\r\n");
        tcsetattr(0, TCSAFLUSH, &tty);
        //lena
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
