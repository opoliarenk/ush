#include "../inc/ush.h"

static void cycle_cop(int *i, char **buff, char *temp) {
   while (temp[(*i)] != ' ' && temp[(*i)] != '\t' 
        && temp[(*i)] != '\r' && temp[(*i)] != '\n' 
        && temp[(*i)] != '\a') {
            (*buff)[(*i)] = temp[(*i)];
            (*i)++;
            if (temp[(*i)] == '\0')
                break;
    } 
}

static int input(char *buff, char *temp) {
    int i = 0;
    char *is_okey = NULL;
    DIR * dir;

    cycle_cop(&i, &buff, temp);
    buff[i] = '\0';
    is_okey = mx_replace_substr(buff, "~", getenv("HOME"));
    dir = opendir(is_okey);
    if (dir == NULL) {
        write(2, "ush: no such user or named directory: ", 38);
        write(2, &buff[1], strlen(buff) - 1);
        write(2, "\n", 1);
        free(is_okey);
        return -1;
    }
    else {
        free(is_okey);
        closedir(dir);
    }
    return 0;
}

static void helper1(int *i, int *size, char *temp) {
    if (temp[(*i)] != '\0') {
        while (temp[(*i)] != ' ' && temp[(*i)] != '\t' 
            && temp[(*i)] != '\r' && temp[(*i)] != '\n' 
            && temp[(*i)] != '\a' && temp[(*i) + 1] != '\0') {
                (*size)++;
                (*i)++;
        } 
    }
}

static int new_line(char *temp) {
    char *buff = NULL;
    int size = 0;

    for (int i = 0; temp[i]; i++) {
        if (temp[i] == '~') {
            size++;
            i++;
            helper1(&i, &size, temp);
            buff = mx_strnew(size);
            if (input(buff, temp) == -1) {
                free(buff);
                return -1;
            }
            free(buff);
            return 0;
        }
    }
    return 0;
}

char *mx_tilde(char **line) {
    char *buf = NULL;

    if ((*line)[0] == '\'' || (*line)[0] == '\"')
        return (*line);
    for (int i = 0; (*line)[i]; i++) {
        if ((*line)[i] == '~') {
            mx_usr_tilde(&(*line)[i + 1], line);
            if (new_line(&(*line)[i]) == -1) {
                return NULL;
            }
            break;//I DONT KNOW
        }
    }
    if (getenv("HOME") != NULL)
        buf = mx_replace_substr((*line), "~", getenv("HOME"));
    else 
        buf = strdup((*line));
    return buf;
}
