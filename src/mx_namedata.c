#include "../inc/ush.h"

static int count(char **name, const char *str) {
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            (*name) = strndup(str, i);
            i++;
            if (str[i] == '\"' || str[i] == '\'')
                i++;
            while (str[i] != '\0' && str[i] != '\"' && str[i] != '\'') {
                j++;
                i++;
            }
            break;
        }
    }
    return j;
}

static void create(char **data, const char *str) {
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            i++;
            if (str[i] == '\"' || str[i] == '\'')
                i++;
            while (str[i] != '\0' && str[i] != '\"' && str[i] != '\'') {
                (*data)[j] = str[i];
                j++;
                i++;
            }
        }
    }
}

void mx_namedata(char **n, char **d, const char *str) {
    char *name = NULL;
    char *data = NULL;

    data = mx_strnew(count(&name, str));
    create(&data, str);
    (*n) = mx_strdup(name);
    (*d) = mx_strdup(data);
    free(name);
    free(data);
}
