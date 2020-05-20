#include "../inc/ush.h"

static bool user_0(t_input *input) {
    char *line;

    input->user = 1;
    mx_clear_view(input, strlen(input->prompt) + 3);
    memset(input->prompt, '\0', sizeof(input->prompt));
    if ((line = getenv("USER"))) {
        strcpy(input->prompt, line);
        // mx_strdel(&line);
    }
    else
        strcpy(input->prompt, "ghost_u$er");
    return true;
}

bool mx_user_prompt(t_input *input) {
    if (input->index == 0) {
        if (input->user == 0) {
            return user_0(input);
        }
        else if (input->user == 1) {
            input->user = 0;
            mx_clear_view(input, strlen(input->prompt) + 3);
            memset(input->prompt, '\0', sizeof(input->prompt));
            strcpy(input->prompt, "u$h");
            return true;
        }
    }
    return true;
}
