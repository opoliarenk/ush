#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	//char *env = mx_file_to_str("/Users/ndykyy/Desktop/ush/builtins/env.txt");
	//char *what_to_export = "HOME";
	char pwd[1024];

	if (argc == 2) {
		chdir(argv[1]);
	}
	else
		chdir("/");
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}
