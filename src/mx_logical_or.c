#include "../inc/ush.h"

static char **split(char *line, int count) {
    char **arr = malloc (sizeof (char *) * (count + 2));
    int len = strlen(line);
    int j = 0;
    int k = 0;
    int i = 0;

    for (; i < len; i++) {
        if ((line[i] == '|' && line[i + 1] == '|' && j != 0) || line[i + 1] == '\0') {
            arr[k] = malloc (sizeof (char) * (j + 1));
            j = 0;
            k++;
        } else if (line[i] != '|' && line[i + 1] != '|')
            j++;
    }
    k = 0;
    j = 0;
    for (i = 0; i < len; i++) {
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

    for (int i = 0; i < len - 1; i++) {
        if (line[i] == '|' && line[i + 1] == '|')
            count++;
    }
    return count;
}

int mx_logical_or(char *line, t_trig *trig, t_var **list) {
    char **arr = split(line, count_of_or(line));
    int i = 0;
    int status_of_work = 1;

    while(arr[i]) {
        if (mx_hardparser(arr[i], trig, list) == 0) { // но сначала функа на проврку пайпов и редирекшинов то есть если ,Назара функа отработала как надо, то прекращаем работу
            status_of_work = 0;
            break;
        }
        i++;
    }
    mx_del_strarr(&arr);
    return status_of_work;
}
