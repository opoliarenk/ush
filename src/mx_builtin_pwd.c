#include "../inc/ush.h"

void mx_builtin_pwd() {
	char pwd[1024];

	getcwd(pwd, sizeof(pwd));
	mx_printstr(pwd);
	mx_printstr("\n");
}
