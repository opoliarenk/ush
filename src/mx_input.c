#include "../inc/ush.h"

static void first_step(t_input *input) {
    input->history_tmp = (t_history_list *)malloc(sizeof(t_history_list));
    // input->history_back = (t_history_list *)malloc(sizeof(t_history_list));

    input->history_back = input->history_head;
    input->cursor = 0;
    input->index = 0;
    dprintf(1, "%s", "u$h> ");
}

char *mx_input(t_input *input) {
    first_step(input);
    while (read(STDIN_FILENO, input->ch, 5) && mx_checkout_char(input)) {
        mx_clear_view(input, 6);
        dprintf(1, "%s%s", "u$h> ", input->history_tmp->data);
        mx_move_cursor(input);
        memset(input->ch, '\0', sizeof(input->ch));
    }
    if (!strlen(input->history_tmp->data)) {
        free(input->history_tmp);
        return NULL;
    }
    mx_push_history(input);
    memset(input->history_tmp->data, '\0', sizeof(input->history_tmp->data));
    free(input->history_tmp);
    return input->history_head->data;
}
