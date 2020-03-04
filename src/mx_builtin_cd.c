#include "../inc/ush.h"

void mx_builtin_cd(char *path) {
	if (path)
		chdir(path);
	else
		chdir("/");
}
