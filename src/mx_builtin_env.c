#include "../inc/ush.h"
#include <signal.h>

void mx_builtin_env(char **env) {
	for (int i = 0; env[i]; i++)
		printf("%s\n",env[i]);
}
