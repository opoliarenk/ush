#include "../inc/ush.h"

void mx_builtin_echo(char **arr, char *origin) {
    int i = 1;
    int point = 2;
    t_echo *echo = (t_echo *)malloc(sizeof(t_echo));
    char **split = mx_strsplit(origin, ' ');

    memset(echo, 0, sizeof(t_echo));
    i = mx_parser_4_echo(arr, echo);
    while (arr[i]) {
        if (arr[i][0] == 127 && arr[i][1] == '\0') {
          i++;
          point++;
          continue;
        }
        mx_echo_part(arr, i, split[point], echo);
        i++;
        point++;
    }
    if (!echo->n)
        mx_printchar(10);
    mx_del_4_echo(split, &echo);
}
