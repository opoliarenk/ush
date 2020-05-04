#include "../inc/ush.h"

void backspace(unsigned int del) {
    for (unsigned int i = 0; i < del; i++)
        dprintf(1, "\b\x1b[0K");
}

void mx_clear_view(t_input *input, int count) {
    backspace(input->index + count);
    input->index = strlen(input->history_tmp->data);
}
