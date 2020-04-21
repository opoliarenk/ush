#include "../inc/ush.h"

static char *help_creat(int fd[2]) {
    char *temp = NULL;
    int fd1[2];
    char a;
    int j = 0;
    int i = 0;

    pipe(fd1);
    while (read(fd[0], &a, 1) > 0) {
        write(fd1[1], &a, 1);
        i++;
    }
    close(fd1[1]);
    close(fd[0]);
    temp = (char*)malloc(sizeof(char) * i + 1);
    while (read(fd1[0], &a, 1) > 0) {
        temp[j] = a;
        j++;
    }
    temp[j] = '\0';
    close(fd1[0]);
    return temp;
}

static char *creating(char **mass, t_trig *trig, t_var **list) {
    char **buff = NULL;
    int i = 0;
    int fd[2];
    int save_fd = dup(1);
    int counter = 0;

    for (int v = 0; mass[v + 1]; v++) {
        if ((strcmp(mass[v], "$") == 0 && strcmp(mass[v + 1], "(") == 0) || strcmp(mass[v + 1], ")") == 0 || strcmp(mass[v + 1], "`") == 0)
            counter++;
    }
    if (counter > 0) {
        for (; strcmp(mass[i], "$") != 0 && strcmp(mass[i + 1], "(") != 0 && strcmp(mass[i], ")") != 0; i++);
        buff = (char **)malloc(sizeof(char *) * i + 1);
        for (i = 0; strcmp(mass[i], "$") != 0 && strcmp(mass[i + 1], "(") != 0 && strcmp(mass[i], ")") != 0; i++)
            buff[i] = strdup(mass[i]);
        buff[i] = NULL;
    } else {
        for (; mass[i]; i++);
        buff = (char **)malloc(sizeof(char *) * i + 1);
        for (i = 0; mass[i]; i++)
            buff[i] = strdup(mass[i]);
        buff[i] = NULL;
    }
    pipe(fd);
    close(1);
    dup2(fd[1], 1);
    mx_builtins(buff, trig, list);
    close(fd[1]);
    dup2(save_fd, 1);
    return help_creat(fd);
}

static char **new_comm(char **mass, char *add) {
    int i = 0;
    int j = 0;
    char **buff = NULL;
    char **add_buff = mx_delim_space(add);

    for (; mass[i] && strcmp(mass[i], "$") != 0 && strcmp(mass[i + 1], "(") != 0 && strcmp(mass[i], ")") != 0; i++);
    for (; add_buff[j]; j++);

    buff = (char **)malloc(sizeof(char *) * (i + j) + 1);
    for (i = 0; mass[i] && strcmp(mass[i], "$") != 0 && strcmp(mass[i + 1], "(") != 0 && strcmp(mass[i], ")") != 0; i++)
        buff[i] = strdup(mass[i]);
    for (j = 0; add_buff[j]; j++)
        buff[i++] = strdup(add_buff[j]);
    buff[i] = NULL;
    return buff;
}

static char **counting_subs(char **mass, t_trig *trig, t_var **list) {
    int comm_count = 0;
    int j = 0;
    int first = 0;
    char **buff_temp = NULL;
    char *temp = NULL;

    char **tmp = NULL;

    for (int i = 0; mass[i]; i++) {
        if (strcmp(mass[i], "`") == 0)
            comm_count++;
        else if (strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0)
            comm_count += 2;
    }
    comm_count /= 2;
    for (; comm_count > 0; comm_count--) {
        for (int i = 0; mass[i]; i++) {
            if (strcmp(mass[i], "`") == 0 || ((strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0)))
                j++;
            if (j == comm_count && first == 0) {
                if (strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0) {
                    temp = creating(&mass[i + 2], trig, list);
                } else 
                    temp = creating(&mass[i + 1], trig, list);
                first++;
                break;
            }
            if (j == comm_count) {
                if (strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0)
                    buff_temp = new_comm(&mass[i + 2], temp);
                else 
                    buff_temp = new_comm(&mass[i + 1], temp);
                free(temp);
                temp = creating(buff_temp, trig, list);
                if (comm_count - 1 == 0) {
                    tmp = new_comm(mass, temp);
                } 
                else
                    mx_del_strarr(&buff_temp);
                break;
            }
        }
        j = 0;
    }
    return tmp;
}

char **mx_subspars(char **mass, t_trig *trig, t_var **list) {
    char **new_mass = NULL;

    for (int i = 0; mass[i]; i++) {
        if ((strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0) || strcmp(mass[i], "`") == 0) {
            new_mass = counting_subs(mass, trig, list);
        }
    }

    return new_mass;
}

