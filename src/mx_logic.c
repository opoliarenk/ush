#include "../inc/ush.h"

static int count_of_ampers(char *line) {
    int len = strlen(line);
    int count = 0;

    for (int i = 0; i < len - 1; i++) {
        if (line[i] == '&' && line[i + 1] == '&')
            count++;
    }
    return count;
}

static char **split(char *line, int count) {
    char **arr = malloc (sizeof (char *) * (count + 2));
    int len = strlen(line);
    int j = 0;
    int k = 0;
    int i = 0;

    for (; i < len; i++) {
        if ((line[i] == '&' && line[i + 1] == '&' && j != 0) || line[i + 1] == '\0') {
            arr[k] = malloc (sizeof (char) * (j + 1));
            j = 0;
            k++;
        } else if (line[i] != '&' && line[i + 1] != '&')
            j++;
    }
    k = 0;
    j = 0;
    for (i = 0; i < len; i++) {
        if (line[i] == '&' && line[i + 1] == '&' && k != 0) {
            arr[j][k + 1] = '\0';
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

void mx_logic(char *mass) {
    //сделать проверку на два спереди и два сзади
    char **arr_ampers = split(mass, count_of_ampers(mass));

    for (int i = 0; arr_ampers[i] != NULL; i++) {
        if (if_there_or(arr_ampers[i]) == 1) {
            if (mx_logical(arr_ampers[i]) == 1)
                break;
        } else {
        //if (func_nazar(arr_ampers[i]) != 0) {
        //  break;
        //}
        }
    }
    mx_del_strarr(arr_ampers);
}
