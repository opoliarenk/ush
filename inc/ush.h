#ifndef ULS_H
#define ULS_H 

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MX_RL_BUFSIZE 1024
#define MX_TOK_BUFSIZE 64
#define MX_TOK_DELIM " \t\r\n\a"

int main(int argc, char **argv);
char *mx_wait_line(void);
char **mx_strsplit(char *line);
char **mx_connectors(char *line);
int mx_semicolon_check(char *line);

#endif
