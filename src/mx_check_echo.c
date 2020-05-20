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

static int brackets(char *line, int *i) {
    (*i)++;
    for (; line[(*i)] != ')'; (*i)++) {
        if (line[(*i)] == '\0') {
            dprintf(2, "Odd number of brackets.\n");
            return 0;
        }
        if (line[(*i)] == '$' && line[(*i) + 1] == '(') {
            if (!brackets(line, i))
                return 0;
        }
        if (line[(*i)] == '\x5c')
            (*i)++;
    }
    return 1;
}

static int acute(char *line, int *i) {
    (*i)++;
    for (; line[(*i)] != '`'; (*i)++) {
        if (line[(*i)] == '\0') {
            dprintf(2, "Odd number of acutes.\n");
            return 0;
        }
        if (line[(*i)] == '\x5c')
            (*i)++;
    }
    return 1;
}

int mx_check_echo(char *line) {
    for (int i = 0; line[i]; i++) {
        if (line[i] == '\x22' || line[i] == '\x27') {
            if (line[i] == '\x22' && !first(line, &i))
                return 0;
            else if (line[i] == '\x27' && !second(line, &i))
                return 0;
        }
        else if (line[i] == '$' && line[i + 1] == '(') {
            if (!brackets(line, &i))
                return 0;
        }
        else if (line[i] == '`') {
            if (!acute(line, &i))
                return 0;
        }
        else if (line[i] == '\x5c')
            i++;
    }
    return mx_odd_slash(line, strlen(line) - 1);
}
