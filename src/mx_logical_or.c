#include "../inc/ush.h"

static void split_helper(char *line, char ***arr) {
    int len = strlen(line);
    int j = 0;
    int k = 0;

    for (int i = 0; i < len; i++) {
        if ((line[i] == '|' && line[i + 1] == '|' && j != 0) || line[i + 1] == '\0') {
            (*arr)[k] = malloc (sizeof (char) * (j + 1));
            j = 0;
            k++;
        } else if (line[i] != '|' && line[i + 1] != '|')
            j++;
    }
}

static char **split(char *line, int count) {
    char **arr = malloc (sizeof (char *) * (count + 2));
    int len = strlen(line);
    int j = 0;
    int k = 0;

    split_helper(line, &arr);
    for (int i = 0; i < len; i++) {
        if (line[i] == '|' && line[i + 1] == '|' && k != 0) {
            arr[j][k] = '\0';
            j++;
            k = 0;
        } else if (line[i] != '|' && line[i + 1] != '|') {
            arr[j][k] = line[i];
            k++; 
        }
    }
    arr[j + 1] = NULL;
    return arr;
}

static int count_of_or(char *line) {
    int len = strlen(line);
    int count = 0;
    struct termios tty;

    for (int i = 0; i < len - 1; i++) {
        if (line[i] == '|' && line[i + 1] == '|' && mx_wspace(&line[i + 2]))
            count++;
        else if (line[i] == '|' && line[i + 1] == '|'
                 && !mx_wspace(&line[i + 2])) {
            count++;
            tcgetattr(0, &tty);
            mx_canon_off();
            mx_cmdor(line);
            tcsetattr(0, TCSAFLUSH, &tty);
        }
    }
    return count;
}

int mx_logical_or(char *line, t_trig *trig, t_var **list) {
    char **arr = split(line, count_of_or(line));
    int i = 0;
    int status_of_work = 1;

    while(arr[i]) {
        if (mx_hardparser(arr[i], trig, list) == 0) { 
            status_of_work = 0;
            break;
        }
        i++;
    }
    mx_del_strarr(&arr);
    return status_of_work;
}
