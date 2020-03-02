#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    char *res = mx_strnew(size);
    char *buf = (char *)ptr;
    unsigned int i;

    if (res == NULL)
        return NULL;
    if (ptr == NULL)
        return res;
    for (i = 0; i < size; i++)
        res[i] = buf[i];
    free(ptr);
    return res;
}
