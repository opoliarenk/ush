#include "../inc/ush.h"

void mx_builtin_unset(char *name) {
	if (name)
		unsetenv(name);
}
