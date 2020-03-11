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
    memset(input->head_line, '\0', sizeof(input->head_line));
    input->cursor = 0;
    input->index = 0;
}

void backspace(unsigned int times) {
    for (unsigned int i = 0; i < times; i++)
        dprintf(1, "\b\x1b[0K");
}

static void clear_view(t_input *input) {
    backspace(input->index + 6);
}

bool checkout_char(t_input *input) {
    if (input->ch[0] == '\n' || input->ch[0] == '\x03'
        || input->ch[0] == '\x7F' 
        || strcmp(input->ch, "\x1b\x5b\x42") == 0
        || strcmp(input->ch, "\x1b\x5b\x41") == 0
        || strcmp(input->ch, "\x1b\x5b\x44") == 0
        || strcmp(input->ch, "\x1b\x5b\x43") == 0
        || input->ch[0] == '\x16' || input->ch[0] == '\t') {

        if (input->ch[0] == '\n'|| input->ch[0] == '\x03') {}

        else if (input->ch[0] == '\x7F') {
            if (input->cursor && input->index) {
                memmove(&input->head_line[input->cursor - 1],
                &input->head_line[input->cursor],
                strlen(input->head_line) - (input->cursor - 1));
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

        else
            strncpy(input->head_line, "exit", 5);
        return false;
    }
    else {
        memmove(input->head_line + input->cursor + 1,
                input->head_line + input->cursor,
                strlen(input->head_line + input->cursor));
        input->head_line[input->cursor] = input->ch[0];
        input->index++;
        input->cursor++;
        return true;
    }
}

char *mx_input(t_input *input) {
    clear_input(input);
    dprintf(1, "%s", "u$h> ");
    while (read(STDIN_FILENO, input->ch, 5) && checkout_char(input)) {
        clear_view(input);
        dprintf(1, "%s%s", "u$h> ", input->head_line);
<<<<<<< HEAD
        cursor(input);
=======
        mx_handle_cursor(input);
>>>>>>> lena
        memset(input->ch, '\0', sizeof(input->ch));
    }
    if (!strlen(input->head_line))
        return NULL;
    return input->head_line;
}
