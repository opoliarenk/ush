#include "../inc/ush.h"

static void mx_bubble_sort_ext(char **arr, int size) {
    char *buf = NULL;

    for (int j = 0; j < size; j++) {
        for (int i = j; i < size - 1; i++) {
            if (mx_strcmp(arr[i], arr[i + 1]) > 0) {
                buf = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = buf;
            }
        }
    }
}

static int strlen_for_2star(char **env) {
	int len = 0;

	while(env[len])
		len++;
	return len;
}

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

void mx_builtin_export(char *name, char *value, char **env) {
	int index_potoka = 1;
	int len_of_env = strlen_for_2star(env);                
	char **dup = strdup_for_2star(env, len_of_env);

	if (name && value)
		setenv(name, value, index_potoka);
	else {
		mx_bubble_sort_ext(dup, len_of_env);
		for (int i = 0; dup[i]; i++)
			printf("%s\n", dup[i]);
	}
}
