#include "../inc/ush.h"

static bool part(char **arr, int i, int j, int *eEn) {
    while (arr[i][j]) {
        if (arr[i][j] == 'n')
            eEn[2] = 1;
        else if (arr[i][j] == 'e')
            eEn[0] = 1;
        else if (arr[i][j] == 'E')
            eEn[1] = 1;
        else
            return false;
        j++;
    }
    return true;
}

static void main_part(char **arr, int i, int j, int *eEn) {
    while (arr[i]) {
        if (arr[i][0] == '-') {
            j = 1;
            if (!part(arr, i, j, eEn))
                break;
        }
        else
            break;
        i++;
    }
}

bool mx_check_for_echoE(char **arr) {
    int i = 1;
    int j = 1;
    int *eEn = (int *)malloc(sizeof(int) * 3);

    eEn[0] = 0;
    eEn[1] = 0;
    eEn[2] = 0;
    if (strcmp(arr[0], "echo") == 0) {
        main_part(arr, i, j, eEn);
        if (eEn[0] == 1 && eEn[1] == 1)
            eEn[1] = 0;
    }
    if (eEn[1] == 1)
        return false;
    else
        return true;
}
