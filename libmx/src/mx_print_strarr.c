#include "../inc/libmx.h" 

void mx_print_strarr(char **arr, const char *delim) {
    int i;

    i = 0;
    if (arr != NULL || delim != NULL) {
        while (arr[i] != NULL) {
            mx_printstr(arr[i]);
            if (arr[i + 1] != NULL)
                mx_printstr(delim);
            i++;
        }
        mx_printstr("\n");
    }
}
