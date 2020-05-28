#include "../inc/ush.h"

static int print_2_type(char *arr, int j, char c) {
    while (arr[j] != c) {
        if (arr[j] == '\\' && arr[j + 1] != c) {
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
    while (arr[j] != '\"') {
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
        else if (arr[j] == '\"' && mx_check_double(&arr[j + 1], '\"'))
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
        if (arr[j] == '\'' && mx_check_double(&arr[j + 1], '\''))
            j = print_2_type(arr, j + 1, '\'');
        else if (arr[j] == '\"' && mx_check_double(&arr[j + 1], '\"')) 
            j = print_2_type(arr, j + 1, '\"');
        else {
            if (arr[j] != 127)
                mx_printchar(arr[j]);
        }
        j++;
    }
}

void mx_echo_part(char **arr, int i, char *split, t_echo *echo) {
    if (echo->E)
        part1_of_cycle(arr[i], split);
    else
        part2_of_cycle(arr[i]);
    if (mx_strlen_for_2star(arr) - i != 1)
        mx_printchar(32);    
}
