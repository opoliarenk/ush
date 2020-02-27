#include "../inc/ush.h"

int while_space(char *line, int i) {
    while (line[i] == ' ')
        i++;
    return i;
}

int mx_semicolon_check(char *line) {
    for (int i = 0; line[i]; i++) {
        i = while_space(line, i);
        if (line[i] == ';') {
            if (line[i + 1] == ';') {
                printf("ush: parse error near `;;'\n");
                return 0;
            }
        }
    }
    return 1;
}
