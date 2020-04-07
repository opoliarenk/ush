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
#include <sys/stat.h>
#include <dirent.h>
#include <malloc/malloc.h>
#include <limits.h>

#define MX_RL_BUFSIZE 1024
#define MX_TOK_BUFSIZE 64
#define MX_TOK_DELIM " \t\r\n\a"
#define MX_IFMT   0170000  /* type of file mask */
#define MX_IFDIR  0040000  /* directory */
#define MX_IFLNK  0120000  /* symbolic link */

typedef struct s_trig{
	bool exit; //trig na exit
	int err;
    char *PWD;
    char *OLDPWD;
} 			   t_trig;

typedef struct s_history_list {
    void *data;
    struct s_history_list *next;
    struct s_history_list *prev;
} 			   t_history_list;

typedef struct s_input {
    char ch[5];
    t_history_list *history_head;
    t_history_list *history_back;
    t_history_list *history_tmp;
    char head_line[ARG_MAX + 1];
    char line[ARG_MAX + 1];
    unsigned int index;
    unsigned int cursor;
    unsigned int try;
} 			   t_input;


int main(int argc, char **argv);
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
char **mx_delim_space(char *line);
char *mx_cut_spaces(char *line);
int mx_rederr(char **mass, t_trig *trig);

int mx_strlen_for_2star(char **env);
void mx_builtins(char **arr, t_trig *trig);
void mx_builtin_env(char **env);
void mx_builtin_export(char *name, char *value, char **env);
void mx_builtin_cd(char **arr, t_trig *trig);
void mx_builtin_pwd(char **arr, t_trig *trig);
void mx_builtin_echo(char **arr);
void mx_builtin_unset(char *name);
void mx_builtin_true(t_trig *trig);
void mx_builtin_false(t_trig *trig);


char *mx_input(t_input *input);
void mx_canon_off(void);

#endif
