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

void mx_builtin_export(char *name, char *value, char **env, t_var **list) {
	int index_potoka = 1;
	int len_of_env = mx_strlen_for_2star(env);                
	char **dup = strdup_for_2star(env, len_of_env);
	t_var *p = *list;

	while(p) {p = p->next;}
	if (name && value)
		setenv(name, value, index_potoka);
	else {
		mx_bubble_sort(dup, len_of_env);
		for (int i = 0; dup[i]; i++)
			printf("%s\n", dup[i]);
	}
}
