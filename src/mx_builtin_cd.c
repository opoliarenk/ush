#include "../inc/ush.h"

void mx_builtin_cd(char **arr, t_trig *trig) {
	char *buf;
	int i = 1;
	char pwd[1024];

	while (arr[i]) {
		if (strcmp(arr[i], "-") == 0) {
		    if (trig->last_cd)
		    	buf = trig->last_cd;
		    else {
		    	getcwd(pwd, sizeof(pwd));
		    	buf = pwd;
		    }
		    mx_printstr(buf);
		    mx_printchar(10);
		}
		// else if (strcmp(arr[i], "-s") == 0)
		// 	
		// else if (strcmp(arr[i], "-P") == 0)
		// 	
		else
			break;
		i++;		
	}
	if (arr[1]) {
		buf = arr[1];
		chdir(buf);
		trig->last_cd = buf;
	}
	else {
		chdir("/");
		trig->last_cd = "/";
	}
}
