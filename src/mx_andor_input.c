#include "../inc/ush.h"

static bool notch2(t_input *input) {
    if (strcmp(input->ch, "\x1b\x5b\x46") == 0) {
        input->cursor = input->index;
        return true;
    }
    else if (input->ch[0] == '\x03') {
        return true;
    }
    else if (input->ch[0] == '\x1a')
        return true;
    else if (!strcmp(input->ch, "\x1b\x5b\x42")
             || !strcmp(input->ch, "\x1b\x5b\x41"))
        return true;
    return false;
}

static bool aif_notch(t_input *input) {
    if (input->ch[0] == '\n')
        return false;
    else if (input->ch[0] == '\x16')
        strncpy(input->history_tmp->data, "exit", 5);
    else if (input->ch[0] == '\x7F')
        return mx_del(input);
    else if (strcmp(input->ch, "\x1b\x5b\x44") == 0)
        return true;
    else if (strcmp(input->ch, "\x1b\x5b\x43") == 0)
        return true;
    else if (strcmp(input->ch, "\x1b\x5b\x48") == 0) {
        input->cursor = 0;
        return true;
    }
    return notch2(input);
}

bool mx_andor_input(t_input *input) {
    if (mx_not_a_char(input)) {
        return aif_notch(input);
    }
    else {
        memmove(input->history_tmp->data + input->cursor + 1,
                input->history_tmp->data + input->cursor,
                strlen(input->history_tmp->data + input->cursor));
        input->history_tmp->data[input->cursor] = input->ch[0];
        input->index++;
        input->cursor++;
        return true;
    }
}
