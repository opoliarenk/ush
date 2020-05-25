#include "../inc/ush.h"

void mx_no_var_is(char *bn, char **temp) {
    char strange[2] = {127, '\0'};
    char *new = mx_good_repl_var((*temp), bn, strange);

    free(*temp);
    (*temp) = strdup(new);
    free(new);
}
