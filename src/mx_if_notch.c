#include "../inc/ush.h"

static bool notch_2(t_input *input) {
    if (strcmp(input->ch, "\x1b\x5b\x46") == 0) {
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
    else if (input->ch[0] == '\t') {
        return true;
    }
    return false;
}

static bool user_prompt(t_input *input) {
    if (input->index == 0) {
        if (input->user == 0) {
            input->user = 1;
            mx_clear_view(input, strlen(input->prompt) + 3);
            memset(input->prompt, '\0', sizeof(input->prompt));
            strcpy(input->prompt, getenv("USER"));
            return true;
        }
        else if (input->user == 1) {
            input->user = 0;
            mx_clear_view(input, strlen(input->prompt) + 3);
            memset(input->prompt, '\0', sizeof(input->prompt));
            strcpy(input->prompt, "u$h");
            return true;
        }
    }
    return true;
}

bool mx_if_notch(t_input *input) {
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
    else if (input->ch[0] == '\x15')
        return user_prompt(input);
    return notch_2(input);
}
