#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    int i = 0;
    t_trig *trig = (t_trig *)malloc(sizeof(t_trig));
    //lena
    t_input *input = (t_input *)malloc(sizeof(t_input)); //struct for input
    input->history_head = (t_history_list *)malloc(sizeof(t_history_list));
    struct termios tty;
    tcgetattr(0, &tty);
    //lena
    //lesha
    t_var *list = (t_var *) malloc (sizeof(t_var));
    list->data = mx_strdup("0");
    list->name_of_data = "?";
    list->next = NULL;
    //lesha
    trig->exit = true;
    trig->err = 0;
    trig->PWD = (char *)malloc(50 * sizeof(char));
    trig->OLDPWD = (char *)malloc(50 * sizeof(char));
    trig->OLDPWD = getenv("PWD");
    trig->PWD = getenv("PWD");
    trig->pids = NULL;
    //
    mx_check_input(trig, list);
    //
    while (trig->exit) {
        //lena
        mx_canon_off();
        line = mx_input(input); //input
        dprintf(1, "\r\n");
        tcsetattr(0, TCSAFLUSH, &tty);
        //lena
        if (line) {
            if (mx_check_echo(line)) {
                mass = mx_connectors(line);
                if (mass && mass[0]) {
                    while(mass[i]) {
                        mx_logic(mass[i], trig, &list);
                        i++;
                    }
                    i = 0;
                }
            }
        }
    }
    free(input);
    system("leaks -q ush");
    return trig->err;
}
