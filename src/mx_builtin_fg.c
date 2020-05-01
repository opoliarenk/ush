#include "../inc/ush.h"

typedef struct s_fg {
    bool str;
    bool num;
    bool cont;
}              t_fg; 

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
    int j = 1;
	t_pid *ppids = trig->pids;
    t_pid *p = trig->pids;
    int status;
    t_fg *fg = (t_fg *)malloc(sizeof(t_fg));

///////////////////////////////////////////////////////////
    if (trig->pids != NULL) {
        t_pid *p1 = trig->pids;
        mx_printstr("\n------------------------\n");
        while (p1) {
            mx_printint(i++);
            mx_printchar('\t');
            mx_printint(p1->npid);
            mx_printchar(10);
            p1 = p1->next;
        }
        mx_printstr("\n------------------------\n");
    }
    i = 1;
///////////////////////////////////////////////////////////
	if (arr[i]) {
		while (arr[i]) {
            memset(fg, 0, sizeof(t_fg));
            if (arr[i][0] == '%') {
                char *res = strdup(&arr[i][1]);

                j = 0;
                while (res[j]) {
                    if (res[j] >= 48 && res[j] <= 57)
                        fg->num = 1;
                    else {
                        fg->str = 1;
                        fg->num = 0;
                        break;
                    }
                    j++;
                }
                j = 1;
                if (trig->pids != NULL) {
                    while (ppids != NULL) {
                        if (fg->num) {
                            if (j == mx_atoi(res)) {
                                fg->cont = 1;
                                break;
                            }
                        }
                        else if (fg->str) {
                            mx_printstr(res);
                            mx_printchar('\t');
                            mx_printstr(strstr(ppids->name_of_pid[0], res));
                            mx_printchar('\n');
                            if (strcmp(res, strstr(ppids->name_of_pid[0], res)) == 0) {
                                fg->cont = 1;
                                break;
                            }
                        }
                        ppids = ppids->next;
                        j++;
                    }
                    if (fg->cont) {
                        kill(ppids->npid, SIGCONT);
                        waitpid(ppids->npid, &status, WUNTRACED);
                        if (status != 4735)
                           pop_front(&p);
                    }
                    else {
                        mx_printerr("fg: ");
                        mx_printerr(arr[i]);
                        mx_printerr(": no such job\n");
                        break;
                    }
                }
                else {
                    mx_printerr("fg: no current job\n");
                    trig->err = 1;
                }
                mx_strdel(&res);
            }
            else {
                mx_printerr("fg: bad option\n");
                break;
                trig->err = 1;
            }
			i++;
		}
	}
	else {
		kill(ppids->npid, SIGCONT);
        waitpid(ppids->npid, &status, WUNTRACED);
        if (status != 4735)
	       pop_front(&ppids);
	}

    ///////////////////////////////////////////////////////////
    i = 1;
    if (trig->pids != NULL) {
        t_pid *p2 = trig->pids;
        mx_printstr("\n------------------------\n");
        while (p2) {
            mx_printint(i++);
            mx_printchar('\t');
            mx_printint(p2->npid);
            mx_printchar(10);
            p2 = p2->next;
        }
        mx_printstr("\n------------------------\n");
    }
    i = 1;
///////////////////////////////////////////////////////////
}
