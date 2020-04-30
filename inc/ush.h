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
#include <errno.h>

#define MX_RL_BUFSIZE 1024
#define MX_TOK_BUFSIZE 64
#define MX_TOK_DELIM " \t\r\n\a"
#define MX_IFMT   0170000  /* type of file mask */
#define MX_IFDIR  0040000  /* directory */
#define MX_IFLNK  0120000  /* symbolic link */

typedef struct s_pid {
    char **name_of_pid;
    pid_t npid;
    struct s_pid *next;
}              t_pid;

typedef struct s_trig{
	bool exit; //trig na exit
    char *linput;
	int err;
    char *PWD;
    char *OLDPWD;
    t_pid *pids;
} 			   t_trig;

typedef struct s_history_list {
    char data[ARG_MAX + 1];
    struct s_history_list *next;
    struct s_history_list *prev;
} 			   t_history_list;

typedef struct s_input {
    char ch[5];
    t_history_list *history_head;
    t_history_list *history_back;
    t_history_list *history_next;
    t_history_list *history_prev;
    t_history_list *history_tmp;
    char head_line[ARG_MAX + 1];
    char line[ARG_MAX + 1];
    unsigned int index;
    unsigned int cursor;
    unsigned int try;
} 			   t_input;

typedef struct s_var {
    char *name_of_data;
    char *data;
    struct s_var *next;
}              t_var;

typedef struct s_echo{
    bool stop;
    bool n;
    bool e;
    bool E;
}              t_echo;

int main(int argc, char **argv);
char *mx_wait_line(void);
char **mx_str_split(char *line);
char **mx_connectors(char *line);
int mx_semicolon_check(char *line);
void mx_logic(char *mass, t_trig *trig, t_var **list);
int mx_logical_or(char *line, t_trig *trig, t_var **list);
char *mx_canon(void);
int mx_red_pipe(char **mass, t_trig *trig, t_var **list);
int mx_redir(char **mass, t_trig *trig, t_var **list);
char **mx_newfor_bults(char **mass);
char **mx_sh_splite(char *line);
char *mx_hardsplit(char *line);
int mx_redirout(char **mass, t_trig *trig, t_var **list);
char **mx_delim_space(char *line);
char *mx_cut_spaces(char *line);
int mx_rederr(char **mass, t_trig *trig, t_var **list);
int mx_redboth(char **mass, t_trig *trig, t_var **list);
void mx_variable(char **mass, t_var **list);
int mx_hardparser(char *line,  t_trig *trig, t_var **list);
int mx_v_exist(char *name, char *data, t_var **list);
void mx_v_out(char **mass, t_var **list);
// char **mx_subspars(char **mass, t_trig *trig, t_var **list);
char **mx_sub(char **mass, t_trig *trig, t_var **list);
char *mx_replace(char *start, char **str, char *temp);
char **mx_end_sub(char **mass, char *str);
int mx_countingw(char *line);
void mx_new_malloc(char **mass, char *line);
int mx_pipe(char **mass, t_trig *trig, t_var **list);
char *mx_tilde(char *line);
int mx_mt(char ***mass);
int mx_doubl_red(char *line, char **mass, t_trig *trig, t_var **list);
void mx_namedata(char **n, char **d, const char *str);
void mx_logic_split(char *line, char ***arr);

int mx_strlen_for_2star(char **env);
void mx_builtins(char **arr, t_trig *trig, t_var **list);
void mx_builtin_env(char **env);
void mx_builtin_export(char **arr, char **env, t_var **list);
void mx_builtin_cd(char **arr, t_trig *trig);
void mx_builtin_pwd(char **arr, t_trig *trig);

void mx_builtin_echo(char **arr, char *origin);
int mx_parser_4_echo(char **arr, t_echo *echo);
bool mx_check_for_echoE(char *arr);
void mx_echo_func_for_slesh(char *str, int j);

void mx_builtin_unset(char **name, t_var **list);
void mx_builtin_fg(char **arr, t_trig *trig);
void mx_builtin_true(t_trig *trig);
void mx_builtin_false(t_trig *trig);
void mx_notbuiltin(char **arr, t_trig *trig, char **environ);

void mx_builtin_which(char **arr, t_trig *trig);
bool mx_is_built_in(char *str);
bool mx_is_slash(char *path);
bool mx_is_command(char *path, bool *flag, int index);
char *mx_strjoin_free(char *s1, const char *s2);

char *mx_input(t_input *input);
void mx_canon_off(void);
void mx_unknown(char **temp);
int mx_check_echo(char *line);
void mx_check_input(t_trig *trig, t_var *list);

void mx_pop_specific_4_pids(t_pid **list, int index);

#endif
