#ifndef ULS_H
#define ULS_H 

#include "../libmx/inc/libmx.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>

#define MX_RL_BUFSIZE 1024
#define MX_TOK_BUFSIZE 64
#define MX_TOK_DELIM " \t\r\n\a"

int main(int argc, char **argv, char **env);
char *mx_wait_line(void);
char **mx_str_split(char *line);
char **mx_connectors(char *line);
int mx_semicolon_check(char *line);
void mx_logic(char *mass);
int mx_logical_or(char *line);
char *mx_canon(void);
int mx_red_pipe(char *line);
int mx_redir(char *line);
char **mx_newfor_bults(char **mass);
char **mx_sh_splite(char *line);





void mx_builtin_env(char **env);
void mx_builtin_export(char *name, char *value, char **env);
void mx_builtin_cd(char *path);
void mx_builtin_pwd();
void mx_builtin_echo(char *str);
#endif
