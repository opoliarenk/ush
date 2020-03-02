#include "../inc/libmx.h"

static int count(int num) {
    int i;

    i = 0;
    if (num == 0)
        return 1;
    if (num < 0)
        i++;
    while (num) {
        num /= 10;
        i++;
    }
    return i;
}

char *mx_itoa(int number) {
    char *res = NULL;
    int i = count(number);
    int j = 0;

    if (number == -2147483648)
        return "-2147483648";
    res = mx_strnew(i);
    if (number < 0) {
        res[0] = '-';
        number *= -1;
        j++;
    }
    for (; i > j; i--) {
        res[i - 1] = number % 10 + 48;
        number /= 10;
    }
    return res;
}
