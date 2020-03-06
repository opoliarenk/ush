#include "../inc/ush.h"

int mx_strlen_for_2star(char **env) {
	int len = 0;

	while(env[len])
		len++;
	return len;
}
