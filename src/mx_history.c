#include "../inc/ush.h"

static int up(t_input *input) {
    if (input->history_back->prev) {
        input->history_back = input->history_back->prev;
        memset(input->history_tmp->data, '\0',
               sizeof(input->history_tmp->data));
        strcpy(input->history_tmp->data, input->history_back->data);
        input->cursor = strlen(input->history_tmp->data);
    }
    return 0;
}

static int down(t_input *input) {
    if (input->history_back
        && input->history_back->next
        && input->history_back->next->next) {
        input->history_back = input->history_back->next;
        memset(input->history_tmp->data, '\0',
               sizeof(input->history_tmp->data));
        strcpy(input->history_tmp->data, input->history_back->data);
        input->cursor = strlen(input->history_tmp->data);
    }
    else if (input->history_back
             && input->history_back->next
             && !input->history_back->next->next) {
        input->history_back = input->history_back->next;
        memset(input->history_tmp->data, '\0',
               sizeof(input->history_tmp->data));
        input->cursor = strlen(input->history_tmp->data);
    }
    return 0;
}

int mx_history(t_input *input) {
    if (!strcmp(input->ch, "\x1b\x5b\x41")) {
        return up(input);
    }
    else if (!strcmp(input->ch, "\x1b\x5b\x42")) {
        return down(input);
    }
    return 1;
}
