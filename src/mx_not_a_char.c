#include "../inc/ush.h"

bool mx_not_a_char(t_input *input) {
    if (input->ch[0] == '\n' || input->ch[0] == '\x04'
        || input->ch[0] == '\x7F'
        || strcmp(input->ch, "\x1b\x5b\x44") == 0
        || strcmp(input->ch, "\x1b\x5b\x43") == 0
        || strcmp(input->ch, "\x1b\x5b\x48") == 0
        || strcmp(input->ch, "\x1b\x5b\x46") == 0
        || !strcmp(input->ch, "\x1b\x5b\x42")
        || !strcmp(input->ch, "\x1b\x5b\x41")
        || input->ch[0] == '\x16' || input->ch[0] == '\x03'
        || input->ch[0] == '\x1a') {
        return true;
    }
    return false;
}
