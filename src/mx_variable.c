#include "../inc/ush.h"

static void namedata(char **n, char **d, const char *str) {
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
    (*n) = mx_strdup(name);
    (*d) = mx_strdup(data);
}

static t_var *create_node(const char *str) {
    t_var *var = (t_var *)malloc(sizeof(t_var));
    char *name = NULL;
    char *data = NULL;

    namedata(&name, &data, str);
    var->name_of_data = strdup(name);
    var->data = strdup(data);
    var->next = NULL;
    free(name);
    free(data);
    return var;
}

static void push_back(t_var **list,const char *str) {
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

static void varcheck(const char *str, t_var **list) {
    char *name = NULL;
    char *data = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[0] == '\"' || str[0] == '\'')
            break;
        if (str[i] == '=') {
            namedata(&name, &data, str);
            if (getenv(name) != NULL) {
                setenv(name, data, 1);
            }
            else {
                if (mx_v_exist(name, data, list) == 0)
                    push_back(list, str);
            }
            free(name);
            free(data);
        }
    }
}

void mx_variable(char **mass, t_var **list) {
    for (int i = 0; mass[i] != NULL; i++)
        varcheck(mass[i], list);
}   
