#include "../inc/ush.h"

// static char *change_str(char *str) {
// 	char *dup = mx_strnew(strlen(str));
// 	int i = 0;

// 	while (str[i] != '\0') {
// 		dup[i] = str[i] == '\n' ? 'n' : str[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return dup;
// }

void mx_builtin_echo(char **arr) {
	bool fl_n = false;
	//bool fl_E = false;
	int i = 1;
	char *buf;

	while (arr[i]) {
		if (strcmp(arr[i], "-n") == 0)
			fl_n = true;
		// else if (strcmp(arr[i], "-e") == 0)
		// 	fl_E = false;
		// else if (strcmp(arr[i], "-E") == 0)
		// 	fl_E = true;
		else
			break;
		i++;		
	}
	while (arr[i + 1]) {
		//if (fl_E)
		//	buf = change_str(arr[i]);
		//else
			buf = arr[i];
		mx_printstr(buf);
		mx_printchar(32);
		i++;
		//if (fl_E)
		//	mx_strdel(&buf);
	}
	mx_printstr(buf);
	if (!fl_n)
		mx_printchar(10);
	else {
		mx_printstr("%\n");
	}
}
