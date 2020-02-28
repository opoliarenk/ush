#include "../inc/ush.h"

char *mx_canon (void) {
    int bufsize = MX_RL_BUFSIZE;
    char ch;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);

    fflush (stdout);
    while (1) {
        read (0, &ch, 1);
        if (ch == EOF || ch == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = ch;
        }
        position++;
        if (position >= bufsize) {
            bufsize += MX_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
        }
    }
}
