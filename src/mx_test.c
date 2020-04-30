#include "../inc/ush.h"

void pop_front(t_pid **head) {
    t_pid *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
        free(*head);
        *head = buf;
    }
}

void mx_test(char **arr, t_trig *trig) {
    t_pid *new = trig->pids;
    int status;

    if (strcmp(arr[0], "fg") == 0) {
        if (new) {
        kill(new->npid, SIGCONT);
        waitpid(new->npid, &status, WUNTRACED);
            if (status != 4735) {
                pop_front(&new);
                trig->pids = new;
            }
        }
    }

    if (new) {
        t_pid *test = trig->pids;
        while(test) {
            mx_printstr(test->name_of_pid[0]);
            mx_printchar('\t');
            mx_printint(test->npid);
            mx_printchar(10);
            test = test->next;
        }
    }

}
