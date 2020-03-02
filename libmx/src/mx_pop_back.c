#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
    t_list *buf = NULL;

    if (head == NULL || *head == NULL)
        return ;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        buf = *head;
        while (buf->next->next != NULL)
            buf = buf->next;
        free(buf->next);
        buf->next = NULL;
    }
}
