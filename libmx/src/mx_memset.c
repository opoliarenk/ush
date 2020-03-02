#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *buf = (char *)b;
    unsigned int i;

    for (i = 0; i < len; i++)
        buf[i] = c;

    return b;
}
