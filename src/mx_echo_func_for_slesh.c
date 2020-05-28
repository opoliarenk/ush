#include "../inc/ush.h"

void mx_echo_func_for_slesh(char *str, int j) {
    if (str[j] == 'a')
        mx_printchar('\a');
    else if (str[j] == 'b')
        mx_printchar('\b');
    else if (str[j] == 'f')
        mx_printchar('\f');
    else if (str[j] == 'n')
        mx_printchar('\n');
    else if (str[j] == 'r')
        mx_printchar('\r');
    else if (str[j] == 't')
        mx_printchar('\t');
    else if (str[j] == 'v')
        mx_printchar('\v');
    else {
        mx_printchar('\\');
        mx_printchar(str[j]);
    }
}
