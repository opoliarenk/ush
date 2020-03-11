#include "../inc/ush.h"

typedef struct s_echo{
    bool stop;
    bool n;
    bool e;
    bool E;
}              t_echo;

void mx_builtin_echo(char **arr) {
    int i = 1;
    int j = 0;
    t_echo *echo = (t_echo *)malloc(sizeof(t_echo));

    memset(echo, 0, sizeof(t_echo));
    while (arr[i]) {
        if (arr[i][j] == '-') {
            while (arr[i][j]) {
                if (arr[i][j] == 'n')
                    echo->n = 1;
                if (arr[i][j] == 'e') {
                    echo->e = 1;
                }
                if (arr[i][j] == 'E') {
                    echo->E = 1;
                }
                j++;
            }
        }
        else
            break;
        i++;
    }
    if (mx_strlen_for_2star(arr) > 2) {
        while (arr[i + 1]) {
            mx_printstr(arr[i]);
            mx_printchar(32);
            i++;
        }
        mx_printstr(arr[i]);
        if (echo->n)
            mx_printstr("%\n");
        else
            mx_printchar(10);
    }
    else
        if (!echo->n)
            mx_printstr("\n");
}
