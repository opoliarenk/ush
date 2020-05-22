#include "../inc/ush.h"

void mx_fill_list(t_var *list) {
	int lvl = mx_atoi(getenv("SHLVL"));

    list->data = mx_strdup("0");
    list->name_of_data =  mx_strdup("?");
    list->next = NULL;
    setenv("SHLVL", mx_itoa(lvl + 1), 1);
}
