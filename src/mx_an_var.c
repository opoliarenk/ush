#include "../inc/ush.h"

void mx_an_var(char **mass, int chang, t_var **list) {
    for (int i = 0; mass[i] != NULL; i++) {
        for (int j = 0; mass[i][j] != '\0'; j++) { 
            if (mass[i][j] == '\'')
                break;
            if (mass[i][j] == '\"')
                break;
            if (chang == 0 && mass[i][j] == '=' && mass[i][j + 1] != '\'') {
                mx_variable(mass, list);
                break;
            }
        }
    }   
}
