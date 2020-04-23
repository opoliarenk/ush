#include "../inc/ush.h"

static char *help_res(int fd[2]) {
    char *temp = NULL;
    int fd1[2];
    char a;
    int i = 0;
    char *newl;

    pipe(fd1);
    while (read(fd[0], &a, 1) > 0) {
        write(fd1[1], &a, 1);
        i++;
    }
    close(fd1[1]);
    close(fd[0]);
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

    pipe(fd);
    close(1);
    dup2(fd[1], 1);
    mx_builtins(buff, trig, list);
    close(fd[1]);
    dup2(save_fd, 1);
    return help_res(fd);
}

static char *workb(char *str, t_trig *trig, t_var **list) {
    char *temp = NULL;
    char **mass_temp = NULL;
    int i = 0;
    char *newl = NULL;
        
    while (str[i] != ')' && str[i] != '`')
        i++;
    temp = (char *)malloc(sizeof(char) * i + 1);
    for (i = 0; str[i] != ')' && str[i] != '`'; i++)
        temp[i] = str[i];
    temp[i] = '\0';
    newl = mx_cut_spaces(temp);
    mass_temp = mx_delim_space(newl);
    free(newl);
    free(temp);
    return result(mass_temp, trig, list);
}

static void creat_pars(char **str, t_trig *trig, t_var **list) {
    int count = mx_count_substr(*str, "$(") + mx_count_substr(*str, "`") / 2; //Tut toge dly `
    int j = 0;
    char *temp = NULL;
    char *repl = NULL;
    int flag = 0; // Dly `

    for (; count > 0; count--) {
        for (int i = 0; (*str)[i]; i++) {
            if ((*str)[i] == '$' && (*str)[i + 1] == '(') 
                j++;
            if ((*str)[i] == '`' && flag == 0) { //DELETE
                j++;
                flag = 1;
            }
            else if ((*str)[i] == '`' && flag == 1) {
                flag = 0;
            }//TO HERE
            if (j == count) { 
                if ((*str)[i] == '$') {
                    temp = workb(&(*str)[i + 2], trig, list);
                    repl = mx_replace(&(*str)[i + 2], str, temp);
                } 
                else { //DELETE IF'S
                    temp = workb(&(*str)[i + 1], trig, list);
                    repl = mx_replace(&(*str)[i + 1], str, temp);
                }
                free(*str);
                *str = mx_strdup(repl);
                j = 0;
                i = 0;
                flag = 0;
                break;
            }
        }
    }
}

char **mx_sub(char **mass, t_trig *trig, t_var **list) {
    char **buff_mass = NULL;
    char **news = NULL;

    for (int i = 0; mass[i]; i++) {
        if ((strstr(mass[i], "$(") != NULL || strstr(mass[i], "`") != NULL) && mass[i][0] != '\'') { // ubrat ili
            creat_pars(&mass[i], trig, list);
            news = mx_end_sub(mass, mass[i]); 
             if ((buff_mass = mx_sub(news, trig, list)) == NULL) {
                return news;
            } 
            else {
                mx_del_strarr(&news);
                news = buff_mass;
            }
            break;
        }
    }
    return news;
}
