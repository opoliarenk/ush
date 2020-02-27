#include "../inc/ush.h"

int while_space(char *line, int i) {
    if (line[i - 1] == ';')
        return 0;
    while (line[i] == ' ')
        i++;
    return i;
}

int mx_semicolon(char *line) {
    int k;

    for (int i = 0; line[i]; i++) {
        i = while_space(line, i);
        if (line[i] == ';') {
            if (line[i + 1] == ';') {
                printf("ush: syntax error near unexpected token `;;'\n");
                return 0;
            }
            else if (line[(k = while_space(line, i + 1))] == ';') {
                printf("ush: syntax error near unexpected token `;'\n");
                return 0;
            }
        }
    }
    return 1;
}
