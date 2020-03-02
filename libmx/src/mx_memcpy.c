#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *buf = (char *)src;
    char *res = (char *)dst;
    unsigned int i;

    for (i = 0; i < n; i++)
        res[i] = buf[i];
    return dst;
}
