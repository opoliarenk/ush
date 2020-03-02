#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    char *smem = (char *)s;
    unsigned int i = n - 1;

    while (i >= 0) {
        if (smem[i] == c)
            return &smem[i];
        i--;
    }
    return NULL;
}
