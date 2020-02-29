#ifndef ULS_H
#define ULS_H 

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MX_RL_BUFSIZE 1024
#define MX_TOK_BUFSIZE 64
#define MX_TOK_DELIM " \t\r\n\a"

int main(int argc, char **argv);
char *mx_wait_line(void);
char **mx_strsplit(char *line);
char **mx_connectors(char *line);
int mx_semicolon(char *line);
bool mx_ifstrstr(const char *haystack, const char *needle);

#endif
