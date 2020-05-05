#include "../inc/ush.h"

static int first(char *line, int *i) {
    (*i)++;
    for (; line[(*i)] != '\x22'; (*i)++) {
        if (line[(*i)] == '\0') {
            dprintf(2, "Odd number of quotes.\n");
            return 0;
        }
        if (line[(*i)] == '\x5c')
            (*i)++;
    }
    return 1;
}

static int second(char *line, int *i) {
    (*i)++;
    for (; line[(*i)] != '\x27'; (*i)++) {
        if (line[(*i)] == '\0') {
            dprintf(2, "Odd number of quotes.\n");
            return 0;
        }
        if (line[(*i)] == '\x5c')
            (*i)++;
    }
    return 1;
}

int mx_check_echo(char *line) {
    for (int i = 0; line[i]; i++) {
        if (line[i] == '\x22') {
            if (!first(line, &i))
                return 0;
        }
        else if (line[i] == '\x27') {
            if (!second(line, &i))
                return 0;
        }
    }
    return 1;
}
