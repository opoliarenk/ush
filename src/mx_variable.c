#include "../inc/ush.h"

static t_var *create_node(char *str) {
    t_var *var = (t_var *)malloc(sizeof(t_var));
    char *name = NULL;
    char *data = NULL;
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            name = strndup(str, i);
            i++;
            while (str[i] != '\0') {
                j++;
                i++;
            }
            break;
        }
    }
    data = mx_strnew(j);
    j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            i++;
            while (str[i] != '\0') {
                data[j] = str[i];
                j++;
                i++;
            }
        }
    }
    var->name_of_data = strdup(name);
    var->data = strdup(data);
    var->next = NULL;
    return var;
}

static void push_back(t_var **list, char *str) {
    t_var *new_var = create_node(str);
    t_var *buff = *list;

    if (buff == NULL) {
        *list = new_var;
        return ;
    }
    while (buff->next != NULL)
        buff = buff->next;
    buff->next = new_var;
}

static void varcheck(char *str, t_var **list) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '=') {
            // if (list == NULL) {
            //     list = create_node(str);
            // } else {
                push_back(list, str);
            // }
        }
    }
}

void mx_variable(char **mass, t_var **list) {
    for (int i = 0; mass[i] != NULL; i++) {
        varcheck(mass[i], list);
    }
}
