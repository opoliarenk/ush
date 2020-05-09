#include "../inc/ush.h"

void mx_push_history(t_input *input) {
    if (strcmp(input->history_head->data, input->history_tmp->data))
        strcpy(input->history_head->data, input->history_tmp->data);
    input->history_next = (t_history_list *)malloc(sizeof(t_history_list));

    input->history_prev = input->history_head->next;
    input->history_head->next = input->history_next;
    strcpy(input->history_next->data, input->history_head->data);
    input->history_next->next = input->history_prev;
    input->history_next->prev = input->history_head;
    if (input->history_prev != NULL)
        input->history_prev->prev = input->history_next;
    input->history_head = input->history_next;
    // free(input->history_next);
}
