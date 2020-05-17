#include "../inc/ush.h"

static void first(char *line, int *i) {
    (*i)++;
    for (; line[(*i)] != '\x22'; (*i)++) {
        if (line[(*i)] == '\x5c') {}
        else {
            dprintf(2, "%c", line[(*i)]);
        }
    }
}

static void second(char *line, int *i) {
    (*i)++;
    for (; line[(*i)] != '\x27'; (*i)++) {
        if (line[(*i)] == '\x5c') {}
        else {
            dprintf(2, "%c", line[(*i)]);
        }
    }
}

static void if_quote(char *line) {
    for (int i = 0; line[i]; i++) {
        if (line[i] == '\x22') {
            first(line, &i);
        }
        else if (line[i] == '\x27') {
            second(line, &i);
        }
        else {
            dprintf(2, "%c", line[i]);
        }
    }
    dprintf(2, "\n");
}

static void slash(char *line) {
    for (int i = 0; line[i]; i++) {
        if (line[i] == '/') {
            dprintf(2, "ush: no such file or directory: ");
            return;
        }
    }
    dprintf(2, "ush: command not found: ");
}

void mx_unknown(char **temp) {
    if (temp[0][0] == '$' && temp[0][1] != '$') {
        exit(0);
    }
    for (int i = 1; temp[0][i]; i++) {
        if (temp[0][i] == '=')
            return;
    }
    slash(temp[0]);
    if_quote(temp[0]);
    exit(127);
}

