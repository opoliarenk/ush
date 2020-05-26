#include "../inc/ush.h"

static void helper1(int fd, int fd1, int *i) {
    char a;

    while (read(fd, &a, 1) > 0) {
        write(fd1, &a, 1);
        (*i)++;
    }
    close(fd1);
    close(fd);
}

static char *help_res(int fd[2]) {
    char *temp = NULL;
    int fd1[2];
    char a;
    int i = 0;
    char *newl;

    pipe(fd1);
    helper1(fd[0], fd1[1], &i);
    temp = (char*)malloc(sizeof(char) * i + 1);
    i = 0;
    while (read(fd1[0], &a, 1) > 0)
        temp[i++] = a;
    temp[i] = '\0';
    newl = mx_cut_spaces(temp);
    close(fd1[0]);
    free(temp);
    return newl;
}

static char *result(char **buff, t_trig *trig, t_var **list) {
    int fd[2];
    int save_fd = dup(1);
    char *newl = NULL;

    pipe(fd);
    close(1);
    dup2(fd[1], 1);
    mx_builtins(buff, trig, list);
    close(fd[1]);
    dup2(save_fd, 1);
    newl = help_res(fd);
    return newl;
}

static char *workb(char *str, t_trig *trig, t_var **list) {
    char *temp = NULL;
    char **mass_temp = NULL;
    int i = 0;
    char *newl = NULL;
    char *res = NULL;
        
    while (str[i] != ')' && str[i] != '`')
        i++;
    if (i == 0)
        return NULL;
    temp = (char *)malloc(sizeof(char) * i + 1);
    for (i = 0; str[i] != ')' && str[i] != '`'; i++)
        temp[i] = str[i];
    temp[i] = '\0';
    newl = mx_cut_spaces(temp);
    mass_temp = mx_delim_space(newl);
    res = result(mass_temp, trig, list);
    mx_del_strarr(&mass_temp);
    free(newl);
    free(temp);
    return res;
}

void mx_workb1(char **str, t_trig *trig, t_var **list, int *j_i_f) {
    char *temp = NULL;
    char *repl = NULL;

    if ((*str)[j_i_f[1]] == '$') {
        temp = workb(&(*str)[j_i_f[1] + 2], trig, list);
        repl = mx_replace(&(*str)[j_i_f[1] + 2], str, temp);
    } 
    else { 
        temp = workb(&(*str)[j_i_f[1] + 1], trig, list);
        repl = mx_replace(&(*str)[j_i_f[1] + 1], str, temp); 
    }
    if (temp)
        free(temp);
    free(*str);
    *str = mx_strdup(repl);
    free(repl);
    j_i_f[0] = 0;
    j_i_f[1] = 0;
    j_i_f[2] = 0;
}
