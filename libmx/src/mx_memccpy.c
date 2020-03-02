#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src,
int c, size_t n) {
    char *buf = (char *)src;
    char *res = (char *)dst;
    unsigned int i;

    for (i = 0; i < n; i++) {
        res[i] = buf[i];
        if (buf[i] == c)
            break;
    }
    if (i == n)
        return NULL;
    i++;
    return (char *)dst + i;
}
