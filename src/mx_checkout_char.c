#include "../inc/ush.h"

static bool not_a_char(t_input *input) {
    if (input->ch[0] == '\n' || input->ch[0] == '\x04'
        || input->ch[0] == '\x7F'
        || strcmp(input->ch, "\x1b\x5b\x44") == 0
        || strcmp(input->ch, "\x1b\x5b\x43") == 0
        || strcmp(input->ch, "\x1b\x5b\x48") == 0
        || strcmp(input->ch, "\x1b\x5b\x46") == 0
        || input->ch[0] == '\x16' || input->ch[0] == '\t'
        || input->ch[0] == '\x03' || input->ch[0] == '\x1a') {
            return true;
    }
    return false;
}

static bool del(t_input *input) {
    if (input->cursor && input->index) {
        memmove(&input->history_tmp->data[input->cursor - 1],
        &input->history_tmp->data[input->cursor],
        strlen(input->history_tmp->data) - (input->cursor - 1));
        input->cursor--;
        input->index--;
    }
    return true;
}

static bool if_notch(t_input *input) {
    if (input->ch[0] == '\n') {}
    else if (input->ch[0] == '\x16')
        strncpy(input->history_tmp->data, "exit", 5);
    else if (input->ch[0] == '\x7F')
        return del(input);
    else if (strcmp(input->ch, "\x1b\x5b\x44") == 0)
        return true;
    else if (strcmp(input->ch, "\x1b\x5b\x43") == 0)
        return true;
    else if (strcmp(input->ch, "\x1b\x5b\x48") == 0) {
        input->cursor = 0;
        return true;
    }
    else if (strcmp(input->ch, "\x1b\x5b\x46") == 0) {
        input->cursor = input->index;
        return true;
    }
    else if (input->ch[0] == '\x04' && input->index == 0) {
        dprintf(1, "exit\n");
        exit(0);
    }
    else if (input->ch[0] == '\x03') {
        memset(input->history_tmp->data,
               '\0', sizeof(input->history_tmp->data));
        return false;
    }
    else if (input->ch[0] == '\x1a')
        return true;
    else if (input->ch[0] == '\t')
        strncpy(input->history_tmp->data, "exit", 5);
    return false;
}

bool mx_checkout_char(t_input *input) {
    if (not_a_char(input)) {
        return if_notch(input);
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
