#include "../inc/ush.h"

static int if_there_exeption(char *mass) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\\') {
            return 0;
        }
    }
    return 1;
}

char *mx_parser_exption(char *mass) {
    if (if_there_exeption(mass) == 0) {
        
    }
}
