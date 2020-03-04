#include "../inc/ush.h"

void mx_builtin_echo(char *str) {
	if (str)
		mx_printstr(str);
	mx_printchar(10);
}
