#include "../inc/ush.h"

void mx_fill_list(t_var *list) {
    list->data = mx_strdup("0");
    list->name_of_data =  mx_strdup("?");
    list->next = NULL;
}
