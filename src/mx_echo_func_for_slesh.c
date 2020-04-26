#include "../inc/ush.h"

void mx_echo_func_for_slesh(char *str, int j) {
    char output;
 
    if (str[j] == 'a')
        output = '\a';
    else if (str[j] == 'b')
        output = '\b';
    else if (str[j] == 'f')
        output = '\f';
    else if (str[j] == 'n')
        output = '\n';
    else if (str[j] == 'r')
        output = '\r';
    else if (str[j] == 't')
        output = '\t';
    else if (str[j] == 'v')
        output = '\v';
    else {
        mx_printchar('\\');
        output = str[j];
    }
    mx_printchar(output);
}
