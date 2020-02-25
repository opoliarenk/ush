#include "../inc/ush.h"

char **mx_strsplit(char *line) {
    int bufsize = MX_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    token = strtok(line, MX_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= bufsize) {
            bufsize += MX_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, MX_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

