#include "../inc/ush.h"

static bool part(char **arr, t_echo *echo, int i, int j) {
    while (arr[i][j]) {
        if (arr[i][j] == 'n')
            echo->n = 1;
        else if (arr[i][j] == 'e')
            echo->e = 1;
        else if (arr[i][j] == 'E')
            echo->E = 1;
        else
            return false;
        j++;
    }
    return true;
}

int mx_parser_4_echo(char **arr, t_echo *echo) {
    int i = 1;
    int j = 1;

    while (arr[i]) {
        if (arr[i][0] == '-') {
            j = 1; 
            if (!part(arr, echo, i, j))
                break;
        }
        else
            break;
        i++;
    }
    if (echo->e && echo->E)
        echo->E = 0;
    return i;
}
