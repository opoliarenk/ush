#include "../inc/ush.h"

static void helper1(char *new, char *buffl, int *pis, int *kk) {
    int h = 0;

    while (h < mx_strlen(buffl)) {
        new[(*kk)] = buffl[h];
        h++;
        (*kk)++;
    }
    (*pis) = 1;
}

char *mx_good_repl_var(char *temp, char *bn, char *buffl) {
    char *new = mx_strnew(mx_strlen(temp) - mx_strlen(bn) + mx_strlen(buffl));
    int h = 0;
    int k = 0;
    int is = 0;

    for (int i = 0; i < mx_strlen(temp); i++) {
        while (is != 1 && bn[h] && temp[i] && temp[i] == bn[h]) {
            i++;
            h++;
        }
        if (h == mx_strlen(bn))
            helper1(new, buffl, &is, &k);
        else 
            i = i - h;
        new[k] = temp[i];
        k++;
        h = 0;
    }
    return new;
}
