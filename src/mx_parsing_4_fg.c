#include "../inc/ush.h" 

void mx_parsing_4_fg(char *res, t_fg *fg) {
    int j = 0;

    while (res[j]) {
        if (res[j] >= 48 && res[j] <= 57)
            fg->num = 1;
        else {
            fg->str = 1;
            fg->num = 0;
            break;
        }
        j++;
    }
}
