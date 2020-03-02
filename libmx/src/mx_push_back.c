#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *new_node = mx_create_node(data);
    t_list *buf = *list;

    if (buf == NULL) {
        *list = new_node;
        return ;
    }
    while (buf->next != NULL)
        buf = buf->next;
    buf->next = new_node;
}
