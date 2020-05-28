#include "../inc/ush.h"

int while_space(char *line, int i) {
    while (line[i] == ' ' || line[i] == ';')
        i++;
    return i;
}

int mx_semicolon_check(char *line) {
    unsigned long k = 0;

    k = while_space(line, 0);
    for (int i = 0; line[i]; i++) {;
        if (line[i] == ';') {
            if (line[i + 1] == ';') {
                printf("ush: parse error near `;;'\n");
                return 0;
            }
        }
    }
    if (k == strlen(line))
        return 0;
    return 1;
}
