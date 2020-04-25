#include "../inc/ush.h"

static int input(char *buff, char *temp) {
    int i = 0;
    char *is_okey = NULL;
    DIR * dir;

    while (temp[i] != ' ' && temp[i] != '\t' 
        && temp[i] != '\r' && temp[i] != '\n' 
        && temp[i] != '\a') {
            buff[i] = temp[i];
            i++;
            if (temp[i] == '\0')
                break;
    } 
    buff[i] = '\0';
    is_okey = mx_replace_substr(buff, "~", getenv("HOME"));
    dir = opendir(is_okey);
    if (dir == NULL) {
        write(2, "ush: no such user or named directory: ", 38);
        write(2, &buff[1], strlen(buff) - 1);
        write(2, "\n", 1);
        return -1;
    }
    else 
        closedir(dir);
    return 0;
}

static int new_line(char *temp) {
    char *buff = NULL;
    int size = 0;

    for (int i = 0; temp[i]; i++) {
        if (temp[i] == '~') {
            size++;
            i++;
            if (temp[i] != '\0') {
                while (temp[i] != ' ' && temp[i] != '\t' 
                && temp[i] != '\r' && temp[i] != '\n' 
                && temp[i] != '\a' && temp[i + 1] != '\0') {
                    size++;
                    i++;
                } 
            }
            buff = mx_strnew(size);
            if (input(buff, temp) == -1)
                return -1;
            return 0;
        }
    }
    return 0;
}

char *mx_tilde(char *line) {
    char *buf = NULL;

    if (line[0] == '\'' || line[0] == '\"')
        return line;
    for (int i = 0; line[i]; i++) {
        if (line[i] == '~') {
            if (new_line(&line[i]) == -1) {
                return NULL;
            }
        }
    }
    buf = mx_replace_substr(line, "~", getenv("HOME"));
    return buf;
}
