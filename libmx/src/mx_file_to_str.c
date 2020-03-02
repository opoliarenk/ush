#include "../inc/libmx.h"

static void cheker(const char *file, int flag) {
	if (flag == 1) {
		mx_printerr("error: file ");
		mx_printerr(file);
		mx_printerr(" does not exist\n");
		exit(1);
	}
	else if (flag == 2) {
		mx_printerr("error: file ");
		mx_printerr(file);
		mx_printerr(" is empty\n");
		exit(1);
	}
	else
		return ;
}

char *mx_file_to_str(const char *file) {
    int fd = open(file, O_RDONLY);
    int len = 0;
    char *str = NULL;
    char c = 0;

    if (fd < 0)
        cheker(file, 1);
    while (read(fd, &c, 1))
        len++;
    close(fd);
    if (len <= 0)
        cheker(file, 2);
    fd = open(file, O_RDONLY);
    str = mx_strnew(len);
    for (int i = 0; read(fd, &c, 1); i++)
        str[i] = c;
    close(fd);
    return str;
}
