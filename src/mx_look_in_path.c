#include "../inc/ush.h"

static void print_not_found(char *arr, t_trig *trig) {
    mx_printerr(arr);
    mx_printerr(" not found\n");
    trig->err = 1;
}

static bool part(bool *flag, char *ways, bool a, char *arr) {
    char *path = mx_strjoin(ways, "/");
    char *str = mx_strjoin_free(path, arr);

    a = mx_is_command(str, flag, 0);
    free(str);
    return a;
}

bool mx_look_in_path(t_trig *trig, char **ways, char *arr, bool *flag) {
    bool a = 0;
    bool triger = 0;

    for (int i = 0; ways[i]; i++) {
        if (mx_is_slash(arr))
            a = mx_is_command(arr, flag, 0);
        else
            a = part(flag, ways[i], a, arr);
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
