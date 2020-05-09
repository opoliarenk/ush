#include "../inc/ush.h"

int main() {
    t_trig *trig = (t_trig *)malloc(sizeof(t_trig));
    t_input *input = (t_input *)malloc(sizeof(t_input));
    input->history_head = (t_history_list *)malloc(sizeof(t_history_list));
    t_var *list = (t_var *)malloc(sizeof(t_var));

    mx_fill_list(list);
    mx_fill_trig(trig);
    mx_check_input(trig, list);
    mx_mainloop(trig, list, input);

    system("leaks -q ush");
    return trig->err;
}
