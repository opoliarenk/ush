#include "../inc/ush.h"

static void first_part(t_trig *trig, t_cd *cd) {
    mx_printerr("cd: string not in pwd: -\n");
    trig->err = 1;
    cd->stop = true;
}

static void second_part(t_cd *cd) {
    cd->back = 1;
    cd->s = false;
    cd->P = false;
}

static void main_part(t_trig *trig, t_cd *cd, char *arr) {
    int j = 1;

    while (arr[j]) {
        if (arr[j] == 's')
            cd->s = 1;
        else if (arr[j] == 'P') {
            if (!cd->s)
                cd->P = 1;
        }
        else {
            mx_printerr("cd: no such file or directory: ");
            mx_printerr(arr);
            mx_printerr("\n");
            trig->err = 1;
            cd->stop = 1;
            break;
        }
        j++;
    }
}

int mx_parser_4_cd(char **arr, t_trig *trig, t_cd *cd) {
    int i = 1;

    while (arr[i]) {
        if (strcmp(arr[i], "-") == 0 && arr[i + 1]) {
            first_part(trig, cd);
            break;
        }
        if (strcmp(arr[i], "-") == 0)
            second_part(cd);
        else {
            if (arr[i][0] == '-')
                main_part(trig, cd, arr[i]);
            else
                break;
        }
        i++;
    }
    return i;
}
