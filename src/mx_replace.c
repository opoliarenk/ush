#include "../inc/ush.h"

static char *wich_creat(int meet, char **str, char *temp, char *buff) {
    char *one = NULL;
    char *final = NULL;

    if (meet == 0) {
        one = mx_strjoin("$(", buff);
        free(buff);
        buff = mx_strjoin(one, ")");
        final = mx_replace_substr(*str, buff, temp);
    } 
    else {
        one = mx_strjoin("`", buff);
        free(buff);
        buff = mx_strjoin(one, "`");
        final = mx_replace_substr(*str, buff, temp);
    }
    free(buff);
    free(one);
    return final;
}

static char *wich_h(char *start, char **str, char *temp, char *buff) {
    int i = 0;
    int meetupf = 0;

    while (start[i]) {
        if (start[i] == ')')
            break;
        if (start[i] == '`') {
            meetupf = 1;
            break;
        }
        i++;
    }
    return wich_creat(meetupf, str, temp, buff);
}

char *mx_replace(char *start, char **str, char *temp) {
    int i = 0;
    char *buff = NULL;
    char *final = NULL;

    while (start[i] != ')' && start[i] != '`')
        i++;
    buff = (char *)malloc(sizeof(char) * i + 1);
    for (int i = 0; start[i] != ')' && start[i] != '`'; i++)
        buff[i] = start[i];
    buff[i] = '\0';
    final = wich_h(start, str, temp, buff);
    return final;
}
