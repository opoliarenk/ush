#include "../inc/ush.h"

void mx_builtin_exit(char **arr, t_trig *trig) {

	if (arr[1] && arr[2]) {
		mx_printerr("exit: too many arguments\n");
		trig->err = 1;
	}
	else if (trig->pids) {
		mx_printerr("There are stopped jobs.\n");
		trig->err = 1;
	}
	else {
		trig->exit = 0;
	    trig->err = mx_atoi(arr[1]);
	}
}
