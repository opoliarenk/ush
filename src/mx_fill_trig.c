#include "../inc/ush.h"

void mx_fill_trig(t_trig *trig) {
	char dir[1024];
	getcwd(dir, 1024);

    if (getenv("_") == NULL)
        setenv("_", "/usr/bin/env", 1);
    if (getenv("PATH") == NULL)
        setenv("PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", 1);
    trig->exit = true;
    trig->err = 0;
    trig->OLDPWD = strdup(dir);
    trig->PWD = strdup(dir);
    trig->pids = NULL;
}
