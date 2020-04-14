#include "../inc/ush.h"

static void set_cursor(t_input *input) {
    unsigned int move_left = input->index - input->cursor;

    for (unsigned int i = 0; i < move_left; i++)
        dprintf(1, "\b");
}

void cursor(t_input *input) {
    if (!strcmp(input->ch, "\x1b\x5b\x43"))
        if (input->cursor < input->index)
            input->cursor++;
    if (!strcmp(input->ch, "\x1b\x5b\x44"))
        if (input->cursor)
            input->cursor--;
    set_cursor(input);
}

static void clear_input(t_input *input) {
    input->cursor = 0;
    input->index = 0;
}

void backspace(unsigned int times) {
    for (unsigned int i = 0; i < times; i++)
        dprintf(1, "\b\x1b[0K");
}

static void clear_view(t_input *input) {
    backspace(input->index + 6);
    input->index = strlen(input->history_tmp->data);
}

int mx_history(t_input *input) {
    if (!strcmp(input->ch, "\x1b\x5b\x41")) {
        if (input->history_back->prev) {
            input->history_back = input->history_back->prev;
            // input->history_tmp = input->history_back;
            memset(input->history_tmp->data, '\0', sizeof(input->history_tmp->data));
            strcpy(input->history_tmp->data, input->history_back->data);
            input->cursor = strlen(input->history_tmp->data);
        }
        return 0;
    }
    else if (!strcmp(input->ch, "\x1b\x5b\x42")) {
        if (input->history_back
            && input->history_back->next
            && input->history_back->next->next) {
            input->history_back = input->history_back->next;
            // input->history_tmp = input->history_back;
            memset(input->history_tmp->data, '\0', sizeof(input->history_tmp->data));
            strcpy(input->history_tmp->data, input->history_back->data);
            input->cursor = strlen(input->history_tmp->data);
        }
        else if (input->history_back
                 && input->history_back->next
                 && !input->history_back->next->next) {
        // else if (input->history_back->next->next == NULL) {
            input->history_back = input->history_back->next;
            // input->history_tmp = input->history_back;
            memset(input->history_tmp->data, '\0', sizeof(input->history_tmp->data));
            input->cursor = strlen(input->history_tmp->data);
        }
        return 0;
    }
    return 1;
}

bool checkout_char(t_input *input) {
    if (input->ch[0] == '\n' || input->ch[0] == '\x03'
        || input->ch[0] == '\x7F'
        || strcmp(input->ch, "\x1b\x5b\x44") == 0
        || strcmp(input->ch, "\x1b\x5b\x43") == 0
        || strcmp(input->ch, "\x1b\x5b\x48") == 0
        || strcmp(input->ch, "\x1b\x5b\x46") == 0
        || input->ch[0] == '\x16' || input->ch[0] == '\t') {
        if (input->ch[0] == '\n') {}
        else if (input->ch[0] == '\x16')
            strncpy(input->history_tmp->data, "exit", 5);
        else if (input->ch[0] == '\x03') {
            memset(input->history_tmp->data, '\0', sizeof(input->history_tmp->data));
        }
        else if (input->ch[0] == '\x7F') {
            if (input->cursor && input->index) {
                memmove(&input->history_tmp->data[input->cursor - 1],
                &input->history_tmp->data[input->cursor],
                strlen(input->history_tmp->data) - (input->cursor - 1));
                input->cursor--;
                input->index--;
            }
            return true;
        }
        else if (strcmp(input->ch, "\x1b\x5b\x44") == 0) {
            return true;
        }
        else if (strcmp(input->ch, "\x1b\x5b\x43") == 0) {
            return true;
        }
        else if (strcmp(input->ch, "\x1b\x5b\x48") == 0) {
            input->cursor = 0;
            return true;
        }
        else if (strcmp(input->ch, "\x1b\x5b\x46") == 0) {
            input->cursor = input->index;
            return true;
        }
        else
            strncpy(input->history_tmp->data, "exit", 5);
        return false;
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

/*struct s_history_list **/ void push(t_input *input) {
    if (strcmp(input->history_head->data, input->history_tmp->data))
        strcpy(input->history_head->data, input->history_tmp->data);
    input->history_next = (t_history_list *)malloc(sizeof(t_history_list));
    input->history_prev = input->history_head->next;
    input->history_head->next = input->history_next;
    strcpy(input->history_next->data, input->history_head->data);
    input->history_next->next = input->history_prev;
    input->history_next->prev = input->history_head;
    if (input->history_prev != NULL)
        input->history_prev->prev = input->history_next;
    input->history_head = input->history_next;
}

char *mx_input(t_input *input) {
    input->history_tmp = (t_history_list *)malloc(sizeof(t_history_list));
    input->history_back = (t_history_list *)malloc(sizeof(t_history_list));
    input->history_back = input->history_head;
    clear_input(input);
    dprintf(1, "%s", "u$h> ");
    while (read(STDIN_FILENO, input->ch, 5) && checkout_char(input)) {
        clear_view(input);
        dprintf(1, "%s%s", "u$h> ", input->history_tmp->data);
        cursor(input);
        memset(input->ch, '\0', sizeof(input->ch));
    }
    if (!strlen(input->history_tmp->data))
        return NULL;
    /*input->history_head = */push(input);
    // memset(input->history_head->data, '\0', sizeof(input->history_head->data));
    return input->history_head->data;
}
