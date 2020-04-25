#include "../inc/ush.h"

bool mx_check_for_echoE(char *arr) {
    char *rule1 = strstr(arr, "echo");

    if (rule1 != NULL) {
        for (int i = 0; arr[i]; i++) {
            if (arr[i] == '-') {
                while (arr[i] != ' ') {
                    if (arr[i] == 'E') {
                        return true;
                    }
                    i++;
                }
            }
        }
    } 
    return false;
}
