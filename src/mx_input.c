#include "../inc/ush.h"

static void first_step(t_input *input) {
    char *line;
    input->history_tmp = (t_history_list *)malloc(sizeof(t_history_list));
    // input->history_back = (t_history_list *)malloc(sizeof(t_history_list));

    input->history_back = input->history_head;
    input->cursor = 0;
    input->index = 0;
    memset(input->prompt, '\0', sizeof(input->prompt));
    if (input->user == 0)
        strcpy(input->prompt, "u$h");
    else if (input->user == 1) {
        if ((line = getenv("USER"))) {
            strcpy(input->prompt, line);
            // mx_strdel(&line);
        }
        else
            strcpy(input->prompt, "ghost_u$er");
    }
    dprintf(1, "%s> ", input->prompt);
}

char *mx_input(t_input *input) {
    first_step(input);
    while (read(STDIN_FILENO, input->ch, 5) && mx_checkout_char(input)) {
        mx_clear_view(input, strlen(input->prompt) + 3);
        dprintf(1, "%s> %s", input->prompt, input->history_tmp->data);
        mx_move_cursor(input);
        memset(input->ch, '\0', sizeof(input->ch));
    }
    memset(input->prompt, '\0', sizeof(input->prompt));
    if (!strlen(input->history_tmp->data)) {
        free(input->history_tmp);
        return NULL;
    }
    mx_push_history(input);
    memset(input->history_tmp->data, '\0', sizeof(input->history_tmp->data));
    free(input->history_tmp);
    return input->history_head->data;
}
