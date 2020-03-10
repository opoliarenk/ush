#include "../inc/ush.h"

static int if_there_exeption(char *mass) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\\' && line[i + 1] == '\\') {
            return 0;
        }
    }
    return 1;
}

void mx_parser_exption(char **mass) {
    for (int i = 0; mass[i] != NULL; i++)
        if (if_there_exeption(mass[i]) == 0) {
            
        }
}
