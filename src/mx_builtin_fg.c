#include "../inc/ush.h"

void pop_front(t_pid **head) {
    t_pid *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
        free(*head);
        *head = buf;
    }
}

void mx_builtin_fg(char **arr, t_trig *trig) {
	int i = 1;
	t_pid *ppids = trig->pids;

	if (arr[i]) {
		while (arr[i]) {
			mx_printstr(arr[i]);
			mx_printchar('\t');
			i++;
		}
		mx_printchar('\n');
	}
	else {
		kill(ppids->npid, SIGCONT);
		pop_front(&ppids);
	}
	if (trig->pids != NULL) {
        while (ppids != NULL) {
            mx_printint(ppids->npid);
            mx_printchar('\n');
            ppids = ppids->next;
        }
    }
    else {
    	mx_printerr("fg: no current job\n");
    	trig->err = 1;
    }
}
