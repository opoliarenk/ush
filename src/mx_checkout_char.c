#include "../inc/ush.h"

static bool not_a_char(t_input *input) {
    if (input->ch[0] == '\n' || input->ch[0] == '\x04'
        || input->ch[0] == '\x7F'
        || strcmp(input->ch, "\x1b\x5b\x44") == 0
        || strcmp(input->ch, "\x1b\x5b\x43") == 0
        || strcmp(input->ch, "\x1b\x5b\x48") == 0
        || strcmp(input->ch, "\x1b\x5b\x46") == 0
        || input->ch[0] == '\x16' || input->ch[0] == '\x03'
        || input->ch[0] == '\x1a' || input->ch[0] == '\t'
        || input->ch[0] == '\x15') {
        return true;
    }
    return false;
}

bool mx_checkout_char(t_input *input) {
    if (not_a_char(input)) {
        return mx_if_notch(input);
    }
    else {
        if (mx_history(input)) {
            memmove(input->history_tmp->data + input->cursor + 1,
                    input->history_tmp->data + input->cursor,
                    strlen(input->history_tmp->data + input->cursor));
            input->history_tmp->data[input->cursor] = input->ch[0];
            input->index++;
            input->cursor++;
        }
        return true;
    }
}
