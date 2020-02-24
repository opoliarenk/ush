#ifndef ULS_H
#define ULS_H 

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MX_RL_BUFSIZE 1024

int main(int argc, char **argv);
char *mx_read_line(void);
char **mx_strsplit(char *line);

#endif
