#include "../inc/ush.h"

int mx_wspace(char *line) {
    int i = 0;

    for (; line[i] && line[i] == ' '; i++) {}
    if (line[i])
        return 1;
    return 0;
}
