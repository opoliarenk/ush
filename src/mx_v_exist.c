#include "../inc/ush.h"

int mx_v_exist(char *name, char *data, t_var **list) {
    t_var *temp = *list;

    if (temp != NULL) {
        while (temp != NULL) {
            if(strcmp(temp->name_of_data, name) == 0) {
                free(temp->data);
                temp->data = strdup(data);
                return 1;
            }
            temp = temp->next;
        }
    }
    return 0;
}

