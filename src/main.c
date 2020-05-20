#include "../inc/ush.h"

int main() {
    t_trig *trig = (t_trig *)malloc(sizeof(t_trig));
    t_input *input = (t_input *)malloc(sizeof(t_input));
    t_var *list = (t_var *)malloc(sizeof(t_var));
    t_var *tmp;

    input->history_head = (t_history_list *)malloc(sizeof(t_history_list));
    mx_fill_list(list); 
    mx_fill_trig(trig);
    mx_check_input(trig, list);
    mx_mainloop(trig, list, input);
    while(list) { 
        tmp = list;
        list = list->next;
        free(tmp->data);
        free(tmp->name_of_data); 
        free(tmp);
    }
    return trig->err;
}
