#include "../inc/ush.h"

char *mx_wait_line(void) {
    int bufsize = MX_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    while (1) {
        // Читаем символ
        c = getchar();
        // При встрече с EOF заменяем его нуль-терминатором и возвращаем буфер
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = c;
        }
        position++;
        // Если мы превысили буфер, перераспределяем блок памяти
        if (position >= bufsize) {
            bufsize += MX_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
        }
    }
}
