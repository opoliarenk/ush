#include "../inc/ush.h"

static int count_of_ampers(char *line) {
    int len = strlen(line);
    int count = 0;
    struct termios tty;

    for (int i = 0; i < len - 1; i++) {
        if (line[i] == '&' && line[i + 1] == '&' && mx_wspace(&line[i + 2]))
            count++;
        else if (line[i] == '&' && line[i + 1] == '&'
                 && !mx_wspace(&line[i + 2])) {
            count++;
            tcgetattr(0, &tty);
            mx_canon_off();
            mx_cmdand(line);
            tcsetattr(0, TCSAFLUSH, &tty);
        }
    }
    return count;
}

static char **split(char *line, int count) {
    char **arr = malloc (sizeof (char *) * (count + 2));
    int len = strlen(line);
    int j = 0;
    int k = 0;

    mx_logic_split(line, &arr);
    for (int i = 0; i < len; i++) {
        if (line[i] == '&' && line[i + 1] == '&' && k != 0) {
            arr[j][k] = '\0';
            j++;
            k = 0;
        } else if (line[i] != '&' && line[i + 1] != '&') {
            arr[j][k] = line[i];
            k++; 
        }
    }
    arr[j + 1] = NULL;
    return arr;
}

static int if_there_or(char *array) {
    int len = strlen(array);

    for (int i = 0; i < len - 1; i++) {
        if (array[i] == '|' && array[i + 1] == '|')
            return 1;
    }
    return 0;
}

static int if_there_amp(char *array) {
    int len = strlen(array);

    for (int i = 0; i < len - 1; i++) {
        if (array[i] == '&' && array[i + 1] == '&')
            return 1;
    }
    return 0;
}

void mx_logic(char *mass, t_trig *trig, t_var **list) {
    char **arr_ampers = NULL;

    if (if_there_amp(mass) == 1)
        arr_ampers = split(mass, count_of_ampers(mass));
    else {
        arr_ampers = malloc (sizeof (char *) * (2));
        arr_ampers[0] = strdup(mass);
        arr_ampers[1] = NULL;
    }
    for (int i = 0; arr_ampers[i] != NULL; i++) {
        if (if_there_or(arr_ampers[i]) == 1) {
            if (mx_logical_or(arr_ampers[i], trig, list) == 1)
                break;
        } else {
            if (mx_hardparser(arr_ampers[i], trig, list) != 0)
                break;
        }
    }
    mx_del_strarr(&arr_ampers);
}
