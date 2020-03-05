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

typedef struct s_trig{
bool exit; //trig na exit
int err;
char *last_cd;
} 			   t_trig;

int main(int argc, char **argv, char **env);
char *mx_wait_line(void);
char **mx_str_split(char *line);
char **mx_connectors(char *line);
int mx_semicolon_check(char *line);
void mx_logic(char *mass, t_trig *trig);
int mx_logical_or(char *line, t_trig *trig);
char *mx_canon(void);
int mx_red_pipe(char **mass, t_trig *trig);
int mx_redir(char **mass, t_trig *trig);
char **mx_newfor_bults(char **mass);
char **mx_sh_splite(char *line);
char *mx_hardsplit(char *line);
int mx_hardparser(char *line,  t_trig *trig);
int mx_redirout(char **mass, t_trig *trig);





void mx_builtins(char **arr, t_trig *trig);
void mx_builtin_env(char **env);
void mx_builtin_export(char *name, char *value, char **env);
void mx_builtin_cd(char **arr, t_trig *trig);
void mx_builtin_pwd();
void mx_builtin_echo(char **arr);
void mx_builtin_unset(char *name);


#endif
