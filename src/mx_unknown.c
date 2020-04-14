#include "../inc/ush.h"

void mx_unknown(char **temp) {
    if (temp[0][5] == '=') {
        dprintf(2, "ush: %s not found\n", &temp[0][6]);
        exit(1);
    }
    for (int i = 6; temp[0][i]; i++) {
        if (temp[0][i] == '=' && temp[0][i + 1] != '=')
            exit(0);
        else if (temp[0][i] == '=' && temp[0][i + 1] == '=') {
            //
        }
    }
    dprintf(2, "ush: command not found : %s\n", &temp[0][5]);
    exit(127);
}
