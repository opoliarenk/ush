#include "../inc/ush.h"

int mx_check_echo(char *line) {
    int i;

    for (i = 0; line[i]; i++) {
        if (line[i] == '\x22') {
            i++;
            for (; line[i] != '\x22'; i++) {
                if (line[i] == '\0') {
                    dprintf(2, "Odd number of quotes.\n");
                    return 0;
                }
                if (line[i] == '\x5c')
                    i++;
            }
        }
        else if (line[i] == '\x27') {
            i++;
            for (; line[i] != '\x27'; i++) {
                if (line[i] == '\0') {
                    dprintf(2, "Odd number of quotes.\n");
                    return 0;
                }
                if (line[i] == '\x5c')
                    i++;
            }
        }
    }
    return 1;
}
