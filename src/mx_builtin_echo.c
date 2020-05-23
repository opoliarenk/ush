#include "../inc/ush.h"

static int print_2_type(char *arr, int j, char c) {
    while (arr[j] != c) {
        if ((arr[j] == '\\' && arr[j + 1] != '\'')
            || (arr[j] == '\\' && arr[j + 1] != '"')) {
            mx_echo_func_for_slesh(arr, j + 1);
            j++;
        }
        else {
            if (arr[j] != 127)
                mx_printchar(arr[j]);
        }
        j++;
    }
    return j;
}

static int print_1_type(char *arr, int j) {
    while (arr[j] != '"') {
        if (arr[j] != 127)
            mx_printchar(arr[j]);
        j++;
    }
    return j;
}

static void part1_of_cycle(char *arr, char *split) {
    int j = 0;

    while (arr[j]) {
        if (arr[j] == '\'' && mx_check_double(&arr[j + 1], '\'')) {
            j++;
            while (arr[j] != '\'') {
                mx_printchar(split[j]);
                j++;
            }
        }
        else if (arr[j] == '"' && mx_check_double(&arr[j + 1], '"'))
            j = print_1_type(arr, j + 1);
        else {
            if (arr[j] == '\\' || arr[j] == 127)
                j++;
            mx_printchar(arr[j]);
        }
        j++;
    }
}

static void part2_of_cycle(char *arr) {
    int j = 0;

    while (arr[j]) {
        if (arr[j] == '\'' && mx_check_double(&arr[j + 1], '\'')) {
            j = print_2_type(arr, j + 1, '\'');
        }
        else if (arr[j] == '"' && mx_check_double(&arr[j + 1], '"')) 
            j = print_2_type(arr, j + 1, '"');
        else {
            if (arr[j] != 127)
                mx_printchar(arr[j]);
        }
        j++;
    }
}

void mx_builtin_echo(char **arr, char *origin) {
    int i = 1;
    int point = 2;
    t_echo *echo = (t_echo *)malloc(sizeof(t_echo));
    char **split = mx_strsplit(origin, ' ');

    memset(echo, 0, sizeof(t_echo));
    i = mx_parser_4_echo(arr, echo);
    while (arr[i]) {
        if (arr[i][0] != 127 && arr[i][1] == '\0') {
            if (echo->E)
                part1_of_cycle(arr[i], split[point]);
            else
                part2_of_cycle(arr[i]);
            if (mx_strlen_for_2star(arr) - i != 1)
                mx_printchar(32);
        }
        i++;
        point++;
    }
    if (!echo->n)
        mx_printchar(10);
    mx_del_4_echo(split, &echo);
}
