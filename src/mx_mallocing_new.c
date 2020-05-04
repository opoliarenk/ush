#include "../inc/ush.h"

static int count_of_word(char **mass) {
    int i = 0;

    while (mass[i])
        i++;
    if (strlen(mass[1]) > 2) 
        i = i - 1;
    else 
        i = i - 2;
    return i;
}

static void creating_new(char **mass, char **new) {
    int k = 0;
    int elem = 0;
    int count = 0;

    for (int i = 1; mass[i]; i++) {
        for (int j = 0; mass[i][j]; j++) {
            if (mass[i][j] == '-' && j == 0 && i == 1)
                j++;
            else {
                new[elem][k] = mass[i][j];
                k++;
                count++;
            }
        }
        if (count != 0) {
            k = 0;
            elem++;
        }
    }
}

char **mx_mallocing_new(char **mass) {
    int count = 0;
    int elem_c = 0;
    char **new_comm = (char **) malloc(sizeof(char *) * count_of_word(mass) + 1);

    for (int i = 1; mass[i]; i++) {
        for (int j = 0; mass[i][j]; j++) {
            if (mass[i][j] == '-' && j == 0 && i == 1)
                j++;
            else
                count++;
        }
        if (count != 0) {
            new_comm[elem_c] = mx_strnew(count);
            count = 0;
            elem_c++;
        }
    }
    new_comm[elem_c] = NULL;
    creating_new(mass, new_comm);
    return new_comm;
}
