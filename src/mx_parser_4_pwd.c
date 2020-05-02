#include "../inc/ush.h"

static void part1(char *arr, t_pwd *pwd, t_trig *trig) {
    int j = 1;

    while (arr[j]) {
        if (arr[j] == 'P')
            pwd->P = 1;
        else if (arr[j] == 'L') {
            if (!pwd->P)
                pwd->L = 1;
        }
        else {
            mx_printerr("pwd: bad option: ");
            mx_printchar(arr[j]);
            mx_printerr("\n");
            trig->err = 1;
            pwd->stop = 1;
            break;
        }
        j++;
    }
}

void mx_parser_4_pwd(char **arr, t_pwd *pwd, t_trig *trig) {
    int i = 1;

    while (arr[i] && pwd->stop != 1) {
        if (arr[i][0] == '-')
            part1(arr[i], pwd, trig);
        else {
            mx_printerr("pwd: too many arguments\n");
            trig->err = 1;
            pwd->stop = 1;
            break;
        }
        i++;
    }
    if (pwd->P)
        pwd->L = 0;
}
