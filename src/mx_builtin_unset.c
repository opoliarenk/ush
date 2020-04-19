#include "../inc/ush.h"

void mx_builtin_unset(char *name, t_var **list) {
	if ((*list) == NULL) {}// UBERI CHTOBI NE RUGALOS NA UNUSED VARIABLE
		
	if (name)
		unsetenv(name);
}
