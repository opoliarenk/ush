#include "../inc/ush.h"

bool mx_del(t_input *input) {
    if (input->cursor && input->index) {
        memmove(&input->history_tmp->data[input->cursor - 1],
        &input->history_tmp->data[input->cursor],
        strlen(input->history_tmp->data) - (input->cursor - 1));
        input->cursor--;
        input->index--;
    }
    return true;
}
