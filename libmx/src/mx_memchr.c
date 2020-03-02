#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    char *smem = (char *)s;
    unsigned int i;

    for (i = 0; *smem && i < n; smem++) {
        if (*smem == c)
            return smem;
        i++;
    }
    return NULL;
}
