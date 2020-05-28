#include "../inc/ush.h"

static void printerr_4_flag_pars(char *arr, int j) {
    mx_printerr("which: bad option: -");
    write(2, &arr[j], 1);
    mx_printerr("\n");
}

static int flag_parser(char **arr, t_trig *trig, bool *flag) {
    int i = 1;

    for (; arr[i]; i++) {
        if (arr[i][0] == '-') {
            for (int j = 1; arr[i][j]; j++) {
                if (arr[i][j] == 'a')
                    flag[0] = 1;
                else if (arr[i][j] == 's')
                    flag[1] = 1;
                else {
                    printerr_4_flag_pars(arr[i], j);
                    trig->err = 1;
                }
            }
        }
        else
            break;
    }
    return i;
}

static void main_part(t_trig *trig, char **ways, char *arr, bool *flag) {
    if (mx_is_built_in(arr) && !flag[1])
        printf("%s: shell built-in command\n", arr);
    if ((!mx_is_built_in(arr) || (mx_is_built_in(arr)
        && flag[0])) && getenv("PATH") != NULL)
        mx_look_in_path(trig, ways, arr, flag);
}

void mx_builtin_which(char **arr, t_trig *trig) {
    bool *flag = (bool *)malloc(sizeof(bool) * 2);
    char **ways = mx_strsplit(getenv("PATH"), ':');
    int i = 0;

    flag[0] = 0;
    flag[1] = 0;
    i = flag_parser(arr, trig, flag);
    while (arr[i]) {
        main_part(trig, ways, arr[i], flag);
        i++;
    }
    if (i < 2) {
        mx_printerr("usage: which [-as] program ...\n");
        trig->err = 1;
    }
    free(flag);
    mx_del_strarr(&ways);
}
