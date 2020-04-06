#include "../inc/libmx.h"

static char *convers(unsigned long temp, unsigned long nbr,
char *res, int i) {
    while (nbr) {
        temp = nbr % 16;
        if (temp <= 9)
            res[i--] = temp + 48;
        else
            res[i--] = temp + 87;
        nbr /= 16;
    }
    return res;
}

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long temp = nbr;
    int i = 0;
    char *res;

    if (nbr == 0) {
        res = mx_strnew(1);
        res[0] = 48;
        return res;
    }
    while (temp) {
        temp /= 16;
        i++;
    }
    res = mx_strnew(i);
    i -= 1;
    res = convers(temp, nbr, res, i);
    return res;
}
