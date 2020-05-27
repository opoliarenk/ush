#include "../inc/ush.h"

void mx_fill_list(t_var *list) {
	int lvl = 0;
	char *str;

    list->data = mx_strdup("0");
    list->name_of_data =  mx_strdup("?");
    list->next = NULL;
    if (getenv("SHLVL") != NULL) {
    	lvl = mx_atoi(getenv("SHLVL"));
    	str = mx_itoa(lvl + 1);
    	setenv("SHLVL", str, 1);
    	mx_strdel(&str);
	}
}
