#include "../inc/ush.h"

static void pop_front_var(t_pid **head) {
    t_pid *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
        mx_del_strarr(&(*head)->name_of_pid);
        free(*head);
        *head = buf;
    }
}

static int variable_list_len(t_pid **head) {
    t_pid *p = (*head);
    int len = 0;

    while (p != NULL) {
        len += 1;
        p = p->next;
    }
    return len;
}

void mx_pop_specific_4_pids(t_pid **list, int index) {
    t_pid *buf = *list;
    t_pid *temp = NULL;
    int size = variable_list_len(list);

    if ((*list != NULL) && (list != NULL)) {
        if (size - 1 >= index) {
            if (index == 0)
                pop_front_var(list);
            else {
                while (index > 1) {
                    buf = buf->next;
                    index--;
                }
                temp = buf->next->next;
                mx_del_strarr(&buf->next->name_of_pid);
                free(buf->next);
                buf->next = temp;
            }
        }
    }
}
