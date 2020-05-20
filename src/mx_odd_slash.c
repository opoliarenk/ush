#include "../inc/ush.h"

int mx_odd_slash(char *line, int i) {
    if (line[i] == '\x5c' && line[i - 1] != '\x5c' && line[i + 1] == '\0') {
        dprintf(2, "Odd number of slash.\n");
        return 0;
    }
    return 1;
}
