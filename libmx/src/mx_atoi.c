#include "../inc/libmx.h"

int mx_atoi(const char *str) {
    int i = 0;
    int sign = 1;
    int num = 0;

    while (mx_is_space(str[i]))
        i++;
    if (str[i] == '-' && mx_isdigit(str[i + 1]))
        sign = -1;
    if ((str[i] == '-' || str[i] == '+') && mx_isdigit(str[i + 1]))
        i++;
    while (mx_isdigit(str[i])) {
        num = num * 10 + (str[i] - 48);
        i++;
    }
    return num * sign;
}
