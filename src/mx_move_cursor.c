#include "../inc/ush.h"

static void cursor(t_input *input) {
    unsigned int move_left = input->index - input->cursor;

    for (unsigned int i = 0; i < move_left; i++)
        mx_printchar('\b');
}

void mx_move_cursor(t_input *input) {
    if (!strcmp(input->ch, "\x1b\x5b\x43"))
        if (input->cursor < input->index)
            input->cursor++;
    if (!strcmp(input->ch, "\x1b\x5b\x44"))
        if (input->cursor)
            input->cursor--;
    cursor(input);
}
