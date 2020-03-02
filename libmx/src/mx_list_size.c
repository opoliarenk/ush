#include "../inc/libmx.h"

int mx_list_size(t_list *list) {
    t_list *buf = list;
    int i = 0;

    while (buf != NULL) {
        i++;
        buf = buf->next;
    }
    return i;
}
