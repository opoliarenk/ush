#include "../inc/ush.h"

char **strdup_for_2star(char **env, int len) {
	char **dup = (char **) malloc (sizeof(char *) * len + 1);
	int i = 0;

	while (env[i]) {
		dup[i] = strdup(env[i]);
		i++;
	}
	dup[i] = NULL;
	return dup;
}

void print_for_export(char **env) {
	int len_of_env = mx_strlen_for_2star(env);                
	char **dup = strdup_for_2star(env, len_of_env);
	
	mx_bubble_sort(dup, len_of_env);
	for (int i = 0; dup[i]; i++)
		printf("%s\n", dup[i]);
	mx_del_strarr(&dup);
}

void mx_builtin_export(char **arr, char **env, t_var **list) {
	t_var *p = *list;
	int i = 1;
	char **split = NULL;

	if (arr[1]) {
		while (arr[i]) {
			split = mx_strsplit(arr[i], '=');
			while(p) {
				if (strcmp(p->name_of_data, arr[i]) == 0
					|| strcmp(p->name_of_data, split[0]) == 0)
					setenv(p->name_of_data, p->data, 1);
				p = p->next;
			}
			p = *list;
			i++;
			mx_del_strarr(&split);
		}
	}
	else
		print_for_export(env);
}
