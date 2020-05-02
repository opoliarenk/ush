#include "../inc/ush.h"

static void print_not_found(char *arr, t_trig *trig) {
    mx_printerr(arr);
    mx_printerr(" not found\n");
    trig->err = 1;
}

static bool look_in_path(t_trig *trig, char **ways, char *arr, bool *flag) {
    bool a = 0;
    bool triger = 0;

    for (int i = 0; ways[i]; i++) {
        if (mx_is_slash(arr))
            a = mx_is_command(arr, flag, 0);
        else {
            char *path = mx_strjoin(ways[i], "/");
            a = mx_is_command(mx_strjoin_free(path, arr), flag, 0);
        }
        if (a == 1) {
            if (!flag[0])
                return a;
            else
                triger = 1;
        }
    }
    if (triger == 0)
        print_not_found(arr, trig);
    return a;
}

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

void mx_builtin_which(char **arr, t_trig *trig) {
    char *path = getenv("PATH");
    bool *flag = (bool *)malloc(sizeof(bool) * 2);
    char **ways = mx_strsplit(path, ':');
    int i = flag_parser(arr, trig, flag);

    for (; arr[i];) {
        if (mx_is_built_in(arr[i]) && !flag[1])
            printf("%s: shell built-in command\n", arr[i]);
        if (!mx_is_built_in(arr[i]) || (mx_is_built_in(arr[i])
            && flag[0]))
            look_in_path(trig, ways, arr[i], flag);
        i++;
    }
    if (i < 2) {
        mx_printerr("usage: which [-as] program ...\n");
        trig->err = 1;
    }
    free(flag);
    mx_del_strarr(&ways);
}
