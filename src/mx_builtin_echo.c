#include "../inc/ush.h"

static void func_for_slesh(char *str, int j) {
    char output;
 
    if (str[j] == 'a')
        output = '\a';
    else if (str[j] == 'b')
        output = '\b';
    else if (str[j] == 'f')
        output = '\f';
    else if (str[j] == 'n')
        output = '\n';
    else if (str[j] == 'r')
        output = '\r';
    else if (str[j] == 't')
        output = '\t';
    else if (str[j] == 'v')
        output = '\v';
    else {
        mx_printchar('\\');
        output = str[j];
    }
    mx_printchar(output);
}

void mx_builtin_echo(char **arr, char *origin) {
    int i = 1;
    int j = 1;
    int point = 2;
    t_echo *echo = (t_echo *)malloc(sizeof(t_echo));
    char **split = mx_strsplit(origin, ' ');

    memset(echo, 0, sizeof(t_echo));
    i = mx_parser_4_echo(arr, echo);
    while (arr[i]) {
        if (echo->E) {
            if (arr[i][0] == '\'') {
                j = 1;
                while (split[point][j] != '\'') {
                    mx_printchar(split[point][j]);
                    j++;
                }
            }
            else if (arr[i][0] == '"') {
                j = 1;
                while (arr[i][j] != '"') {
                    mx_printchar(arr[i][j]);
                    j++;
                }
            }
            else {
                j = 0;
                while (arr[i][j]) {
                    mx_printchar(arr[i][j]);
                    j++;
                }
            }
        }
        else {
            if (arr[i][0] == '\'') {
                j = 1;
                while (arr[i][j] != '\'') {
                    if (arr[i][j] == '\\'&& arr[i][j + 1] != '\'') {
                        func_for_slesh(arr[i], j + 1);
                        j++;
                    }
                    else
                        mx_printchar(arr[i][j]);
                    j++;
                }
            }
            else if (arr[i][0] == '"') {
                j = 1;
                while (arr[i][j] != '"') {
                    if (arr[i][j] == '\\' && arr[i][j + 1] != '"') {
                        func_for_slesh(arr[i], j + 1);
                        j++;
                    }
                    else
                        mx_printchar(arr[i][j]);
                    j++;
                }
            }
            else {
                j = 0;
                while (arr[i][j]) {
                    mx_printchar(arr[i][j]);
                    j++;
                }
            }
        }
        if (mx_strlen_for_2star(arr) - i != 1)
            mx_printchar(32);
        i++;
        point++;
    }
    mx_del_strarr(&split);
    if (!echo->n)
        mx_printchar(10);
        // ///
        // i = 0; j = 0;
        // mx_printstr("\n------------------------\n");
        //     while (arr[i]) {
        //         while (arr[i][j]) {
        //             mx_printchar(arr[i][j]);
        //             mx_printchar(32);
        //             j++;
        //         }
        //         j = 0;
        //         i++;
        //         mx_printchar(10);
        //     }
        //     //
        // ///
        // i = 0; j = 0;
        // mx_printstr("\n------------------------\n");
        // mx_printstr(origin);
        // mx_printstr("\n------------------------\n");
}
