#include "../inc/ush.h"

void mx_logic_split(char *line, char ***arr) {
    int j = 0;
    int k = 0;
    int i = 0;
    int len = strlen(line);

    for (; i < len; i++) {
        if ((line[i] == '&' && line[i + 1] == '&' && j != 0) 
        || line[i + 1] == '\0') {
            (*arr)[k] = malloc (sizeof (char) * (j + 1));
            j = 0;
            k++;
        }
        else if (line[i] != '&' && line[i + 1] != '&')
            j++;
    }
}


