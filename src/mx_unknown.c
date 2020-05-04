#include "../inc/ush.h"

void mx_unknown(char **temp) {
    if (temp[0][0] == '$' && temp[0][1] != '$') {
        exit(0);
    }
    for (int i = 1; temp[0][i]; i++) {
        if (temp[0][i] == '=')
            return;
    }
    dprintf(2, "ush: command not found: %s\n", temp[0]);
    exit(127);
}

