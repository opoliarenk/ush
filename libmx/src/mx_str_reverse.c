#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    int i = mx_strlen(s) - 1;
    int j = 0;
    char q;

    while (i > j) {
        q = s[i];
        s[i] = s[j];
        s[j] = q;
        i--;
        j++;
    }
}
