#include "../inc/ush.h"

void mx_usr_tilde(char *temp, char **temp1) {
    char *usr = getenv("USER");
    char *cmp = mx_strjoin("~", usr);
    int is = 0;
    char *new = NULL;

    for (int i = 0; temp[i] != '/' && temp[i] != ' ' && temp[i] != '\0'; i++) {
        if (usr[i] != temp[i]) {
            is = 1;
            break;
        }
    }
    if (is == 0) {
        new = mx_replace_substr((*temp1), cmp, "~");
        free(*temp1);
        *temp1 = strdup(new);
        free(new);
    }
    free(cmp);
}
