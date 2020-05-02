#include "../inc/ush.h"

void mx_pid_pop_front(t_pid **head) {
    t_pid *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
        free(*head);
        *head = buf;
    }
}
