#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *cdst = (char *)dst;
    char *csrc = (char *)src;
    char *temp = mx_strnew(len);
    unsigned int i;

    for (i = 0; i < len; i++)
        temp[i] = csrc[i];
    for (i = 0; i < len; i++)
        cdst[i] = temp[i];
    return cdst;
}
