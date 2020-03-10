#include "../inc/ush.h"

static void set_cursor(t_input *input) {
    unsigned int move_left = input->index - input->cursor;

    for (unsigned int i = 0; i < move_left; i++)
        printf("\b");
}

void mx_handle_cursor(t_input *input) {
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
    memset(input->back_line, '\0', sizeof(input->back_line));
    memset(input->line, '\0', sizeof(input->line));
    input->cursor = 0;
    input->index = 0;
}

// bool checkout_char(t_input *input) {
//     // проверяю на новую строку и ^C
//     if (input->ch[0] == '\n' || input->ch[0] == '\x03') {
//         return false;
//     }
//     //------------------------------

//     // разделяю на две строки
//     if (input->cursor != input->index) {
//         strncpy(input->line, input->head_line, input->cursor);
//         strncpy(input->back_line, &input->head_line[input->cursor], input->index);
//         strcpy(input->head_line, input->line);
//     }
//     else {
//         memset(input->back_line, '\0', sizeof(input->back_line));
//     }
//     //-----------------------

//     // проверка (удаление символа) (лево) (право)
//     if (input->index != 0 && input->cursor != 0) {
//         if (input->ch[0] == '\x7F') {
//             // realloc(input->head_line, input->cursor);
//             dprintf(1, "\b\x1b[0K");
//             input->cursor--;
//         }
//     }
//     // mx_handle_cursor(input);
//     //------------------------------------------------------------

//     // вывод истории (вверх) (вниз)

//     //
//     if (input->ch[0] != '\x7F' && strcmp(input->ch, "\x1b\x5b\x44") && strcmp(input->ch, "\x1b\x5b\x44")) {
//         input->head_line[input->cursor++] = input->ch[0];
//         mx_strjoin(input->head_line, input->back_line);
//         input->index++;
//     }

//     return true;
// }

void backspace(unsigned int times) {
    for (unsigned int i = 0; i < times; i++)
        dprintf(1, "\b\x1b[0K");
}

static void clear_view(t_input *input) {
    backspace(input->index + 6);
    dprintf(1, "%s%s", "u$h> ", input->head_line);
    backspace(input->index + 6);
}

bool checkout_char(t_input *input) {
    if (input->ch[0] == '\n' || input->ch[0] == '\x03' || input->ch[0] == '\x7F' 
       || strcmp(input->ch, "\x1b\x5b\x42") == 0
       || strcmp(input->ch, "\x1b\x5b\x41") == 0
       || strcmp(input->ch, "\x1b\x5b\x44") == 0
       || strcmp(input->ch, "\x1b\x5b\x43") == 0
       || input->ch[0] == '\x16') {
            if (input->ch[0] == '\n'|| input->ch[0] == '\x03') {}

            else if (input->ch[0] == '\x7F') {
                if (input->cursor > 0) {
                    strcat(input->head_line, "\b\x1b[0K");
                    input->cursor--;
                    input->index--;
                }
                return true;
            }

            else if (strcmp(input->ch, "\x1b\x5b\x44") == 0) {
                if (input->cursor > 0) {
                    strcat(input->head_line, "\x1b[1D");
                    input->cursor--;
                }
                return true;
            }

            else if (strcmp(input->ch, "\x1b\x5b\x43") == 0) {
                if (input->cursor < input->index) {
                    strcat(input->head_line, "\x1b[1C");
                    input->cursor++;
                }
                return true;
            }

            else
                strncpy(input->head_line, "exit", 5);
            return false;
        }
    else {
        strcat(input->head_line, &input->ch[0]);
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
        // mx_handle_cursor(input);
        memset(input->ch, '\0', sizeof(input->ch));
        // fflush(stdout);
    }
    return input->head_line;
}
