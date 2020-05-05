#include "../inc/ush.h"

static void first_step(t_input *inp) {
    inp->history_tmp = (t_history_list *)malloc(sizeof(t_history_list));

    inp->cursor = 0;
    inp->index = 0;
    dprintf(1, "%s", "cmdand> ");
}

void mx_cmdand(char *line) {
    t_input *inp = malloc(sizeof(t_input));

    first_step(inp);
    while (read(STDIN_FILENO, inp->ch, 5) && mx_andor_input(inp)) {
        mx_clear_view(inp, 10);
        dprintf(1, "%s%s", "cmdand> ", inp->history_tmp->data);
        mx_move_cursor(inp);
        memset(inp->ch, '\0', sizeof(inp->ch));
    }
    if (!strlen(inp->history_tmp->data)) {
        mx_printchar(10);
        mx_cmdand(line);
    }
    mx_strcat(line, inp->history_tmp->data);
    memset(inp->history_tmp->data, '\0', sizeof(inp->history_tmp->data));
    free(inp->history_tmp);
    free(inp);
    mx_printchar(10);
}
