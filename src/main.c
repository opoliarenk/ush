#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    int i = 0;
    t_trig *trig = (t_trig *)malloc(sizeof(t_trig));

    trig->exit = true;
    trig->err = 0;
    while (trig->exit) {
        printf("u$h> ");
        line = mx_wait_line(); //mx_canon();
        if (line) {
            mass = mx_connectors(line);
            if (mass[0]) {
                while(mass[i]) {
                    mx_logic(mass[i], trig);
                    i++;
                }
                i = 0;
            }
            //mx_builtins(mass, trig);
        }
    }
    return trig->err;
}
