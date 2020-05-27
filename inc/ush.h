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
    bool is_cdP;
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
    int user;
    char prompt[ARG_MAX + 1];
    unsigned int index;
    unsigned int cursor;
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

typedef struct s_fg {
    bool str;
    bool num;
    bool cont;
}              t_fg;

typedef struct s_cd{
    bool stop;
    bool back;
    bool s;
    bool P;
}              t_cd;

typedef struct s_pwd{
    bool stop;
    bool L;
    bool P;
}              t_pwd;

typedef struct s_env{
    bool stop;
    bool i;
    bool u;
    bool P;
}              t_env;

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
char **mx_sub(char **mass, t_trig *trig, t_var **list);
char *mx_replace(char *start, char **str, char *temp);
char **mx_end_sub(char **mass, char *str);
int mx_countingw(char *line);
void mx_new_malloc(char **mass, char *line);
int mx_pipe(char **mass, t_trig *trig, t_var **list);
char *mx_tilde(char **line);
int mx_mt(char ***mass);
int mx_doubl_red(char *line, char **mass, t_trig *trig, t_var **list);
void mx_namedata(char **n, char **d, const char *str);
void mx_logic_split(char *line, char ***arr);
char *mx_if_P(t_trig *trig, char **arr);
int mx_var_rep_count(char **temp);
void mx_var_rep_crt(char **temp, char **buff_n);
void mx_an_var(char **mass, int chang, t_var **list);
int mx_hspl_count(char *line);
void mx_hspl_cr(char *line, char **new, int *q, int *k);
void mx_hspl_cr1(char *line, char **new, int *k, int *q);
char *mx_hash(char *line);
void mx_pre_substr(char **newl);
void mx_sky_doubt(char *line, int *i, int *j_k_c_ko, char ***mass);
void mx_sub_pars(char *line, int *i, int *j_k_c_ko, char ***mass);
void mx_sub_doll_p(char *line, int *i, int *j_k_c_ko, char ***mass);
void mx_doubl_d(char *line, int *i, int *j_k_c_ko, char ***mass);
void mx_countingwh(char *line, int *i, int *kol);
void mx_countingwh1(char *line, int *i);
void mx_new_m_help(char *line, char ***mass, int *j_e_k, int *i);
void mx_new_m_sd(char *line, char ***mass, int *j_e_k, int *i);
void mx_new_s_d(char *line, char ***mass, int *j_e_k, int *i);
void mx_new_str_d(char *line, char ***mass, int *j_e_k, int *i);
void mx_sub_counts(char **str, int *j_i_f);
void mx_workb1(char **str, t_trig *trig, t_var **list, int *j_i_f);
int mx_red_bh(char **mass, int i, char *str, int *fd);
void mx_pipe_help(int *one_zero_fd, char **buff, t_trig *trig, t_var **list);
void mx_last_coms(char **temp);
void mx_no_var_is(char *bn, char **temp);
char **mx_env_var(char ***environ, char **arr);
int mx_find_env(char *environ, char *buff);
int mx_env_exe(char **arr, char **envi, t_trig *trig);
void mx_env_unk(char **arr, char **environ, t_trig *trig);
void mx_usr_tilde(char *temp, char **temp1);
char *mx_good_repl_var(char *temp, char *bn, char *buffl);

int mx_strlen_for_2star(char **env);
void mx_builtins(char **arr, t_trig *trig, t_var **list);
void mx_builtin_env(char **environ, char **arr, t_trig *trig);
void mx_env_i(char **mass, t_trig *trig);
void mx_env_u(char **mass, t_trig *trig, char **environ);
void mx_env_P(char **mass, t_trig *trig, char **environ);
void mx_env_not(char **arr, t_trig *trig, char **environ);
char **mx_mallocing_new(char **mass);
void mx_builtin_export(char **arr, char **env, t_var **list);

void mx_builtin_cd(char **arr, t_trig *trig);
int mx_parser_4_cd(char **arr, t_trig *trig, t_cd *cd);
char *mx_part1_4_cd(char **arr, t_trig *trig, t_cd *cd, int i);
void mx_cd_back(t_trig *trig);
void mx_cd_s(char *path, t_trig *trig);
void mx_cd_P(char *path, t_trig *trig);

void mx_builtin_pwd(char **arr, t_trig *trig);
void mx_parser_4_pwd(char **arr, t_pwd *pwd, t_trig *trig);

void mx_builtin_echo(char **arr, char *origin);
int mx_parser_4_echo(char **arr, t_echo *echo);
bool mx_check_for_echoE(char *arr);
void mx_echo_func_for_slesh(char *str, int j);
void mx_del_4_echo(char **split, t_echo **echo);
bool mx_check_double(char *arr, char c);
void mx_echo_part(char **arr, int i, char *split, t_echo *echo);

void mx_builtin_fg(char **arr, t_trig *trig);
void mx_pid_pop_front(t_pid **head);
void mx_parsing_4_fg(char *res, t_fg *fg);
int mx_check_list_4_fg(char *res, t_pid **ppids, t_fg *fg);
void mx_printname_4_fg(t_pid *ppids);
bool mx_kill_4_fg(t_pid *ppids, t_trig **trig, t_fg *fg, int j);

void mx_builtin_exit(char **arr, t_trig *trig);
void mx_builtin_unset(char **name, t_var **list);
void mx_builtin_true(t_trig *trig);
void mx_builtin_false(t_trig *trig);
void mx_notbuiltin(char **arr, t_trig *trig, char **environ);

void mx_builtin_which(char **arr, t_trig *trig);
bool mx_is_built_in(char *str);
bool mx_is_slash(char *path);
bool mx_is_command(char *path, bool *flag, int index);
char *mx_strjoin_free(char *s1, const char *s2);
bool mx_look_in_path(t_trig *trig, char **ways, char *arr, bool *flag);

char *mx_input(t_input *input); //auditor
void mx_move_cursor(t_input *input); //auditor_leaks
void mx_canon_off(void); //auditor_leaks
void mx_unknown(char **temp); //auditor_leaks
int mx_check_echo(char *line); //auditor_leaks
void mx_check_input(t_trig *trig, t_var *list); //auditor_leaks
int mx_history(t_input *input); //auditor_leaks
bool mx_checkout_char(t_input *input); //auditor_leaks
void mx_push_history(t_input *input); //auditor
void mx_cmdand(char *line); //auditor
bool mx_andor_input(t_input *input); //auditor_leaks
void mx_cmdor(char *line); //auditor_leaks
int mx_wspace(char *line); //auditor_leaks
void mx_clear_view(t_input *input, int count); //auditor_leaks
bool mx_not_a_char(t_input *input); //auditor_leaks
bool mx_del(t_input *input); //auditor_leaks
bool mx_if_notch(t_input *input); //auditor_leaks
void mx_fill_list(t_var *list);
void mx_fill_trig(t_trig *trig);
void mx_mainloop(t_trig *trig, t_var *list, t_input *input);
bool mx_user_prompt(t_input *input);
int mx_odd_slash(char *line, int i);

void mx_pop_specific_4_pids(t_pid **list, int index);
void mx_signals();

#endif
