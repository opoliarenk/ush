#include "../inc/ush.h"

static int while_space(char *line, int i) {
    int k = i + 1;

    while (line[k] == ' ') {
        k++;
    }
    if (line[k] == ';')
        return k;
    return i;
}

static void auditor_1 (char *line, char **arr) {
    int k = 0;
    int j = 0;
    int len = strlen(line);
    int h = 0;

    for (int i = 0; i < len; i++) {
        if ((line[i] == ';' && j != 0) || line[i + 1] == '\0') {
            arr[k] = malloc (sizeof (char) * (j + 1));
            j = 0;
            k++;
        }
        else if (line[i] == ';' && (h = while_space(line, i)) != i) {
            i = h;
            j = 0;
        }
        else if (line[i] != ';') {
            j++;
        }
    }
}

static char **split(char *line, int count) {
    char **arr = malloc (sizeof (char *) * (count + 2));
    int len = strlen(line);
    int j = 0;
    int k = 0;
    int h = 0;

    auditor_1(line, arr);
    for (int i = 0; i < len; i++) {
        if (line[i] == ';' && (h = while_space(line, i)) != i) {
            i = h;
        }
        else if (line[i] == ';' && k != 0) {
            arr[j][k] = '\0';
            j++;
            k = 0;
        }
        else if (line[i] != ';') {
            arr[j][k] = line[i];
            k++; 
        }
    }
    arr[j + 1] = NULL;
    return arr;
}

char **mx_connectors(char *line) {
    char **mass = NULL;
    int sep = 0;

    if (mx_semicolon_check(line)) {
        for (int i = 0; line[i]; i++) 
            if (line[i] == ';' && i != 0)
                sep++;
        if (sep > 0)
            mass = split(line, sep);
        else {
            mass = malloc (sizeof (char *) * (2));
            mass[0] = strdup(line);
            mass[1] = NULL;
        }
    }
    return mass;
}

//not sure, that it work correctly
