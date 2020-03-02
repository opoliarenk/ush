#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long base = 1;
    unsigned long res = 0;
    int i;

    i = mx_strlen(hex) - 1;
    while (i >= 0) {

        if (hex[i] >= '0' && hex[i] <= '9')
            res += (hex[i] - 48) * base;
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            res += (hex[i] - 55) * base;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            res += (hex[i] - 87) * base;
        base *= 16;
        i--;
    }
    return res;
}
