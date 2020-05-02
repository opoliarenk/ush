#include "../inc/ush.h"

void backspace(unsigned int del) {
    for (unsigned int i = 0; i < del; i++)
        dprintf(1, "\b\x1b[0K");
}

static void clear_view(t_input *input) {
    backspace(input->index + 6);
    input->index = strlen(input->history_tmp->data);
}

char *mx_input(t_input *input) {
    input->history_tmp = (t_history_list *)malloc(sizeof(t_history_list));
    input->history_back = (t_history_list *)malloc(sizeof(t_history_list));
    input->history_back = input->history_head;
    input->cursor = 0;
    input->index = 0;
    dprintf(1, "%s", "u$h> ");
    while (read(STDIN_FILENO, input->ch, 5) && mx_checkout_char(input)) {
        clear_view(input);
        dprintf(1, "%s%s", "u$h> ", input->history_tmp->data);
        mx_move_cursor(input);
        memset(input->ch, '\0', sizeof(input->ch));
    }
    if (!strlen(input->history_tmp->data))
        return NULL;
    mx_push_history(input);
    return input->history_head->data;
}
