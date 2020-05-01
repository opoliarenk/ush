#include "../inc/ush.h"

typedef struct s_fg {
    bool str;
    bool num;
    bool cont;
}              t_fg; 

void mx_pid_pop_front(t_pid **head) {
    t_pid *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
        free(*head);
        *head = buf;
    }
}

void mx_parsing_4_fg(char *res, t_fg *fg) {
    int j = 0;

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
}

int mx_check_list_4_fg(char *res, t_pid *ppids, t_fg *fg) {
    int j = 1;

    while (ppids != NULL) {
        if (fg->num) {
            if (j == mx_atoi(res)) {
                fg->cont = 1;
                break;
            }
        }
        else if (fg->str && strstr(ppids->name_of_pid[0], res)) {
            if (strcmp(res, strstr(ppids->name_of_pid[0], res)) == 0) {
                fg->cont = 1;
                break;
            }
        }
        ppids = ppids->next;
        j++;
    }
    mx_printstr(ppids->name_of_pid[0]);////////////LYOSHA HERE TEST
    return j;
}

static bool vykonannya(t_pid *ppids, t_trig *trig, t_fg *fg, int j) {
    int status;
    t_pid *p = trig->pids;

    mx_printstr(ppids->name_of_pid[0]);////////////LYOSHA HERE TEST
    if (fg->cont) {
        if (ppids) {
            kill(ppids->npid, SIGCONT);
            waitpid(ppids->npid, &status, WUNTRACED);
            if (WIFEXITED(status) == true){
                mx_printstr("\nFINESHED\n");
                sleep(5);
            }
            if (status != 4735) {
                mx_pop_specific_4_pids(&p, j - 1);
                trig->pids = p;
            }
        }
    }
    else
        return false;
    return true;
}

static void bez_umovy(t_pid *ppids, t_trig *trig) {
    int status;

    if (ppids) {
        kill(ppids->npid, SIGCONT);
        waitpid(ppids->npid, &status, WUNTRACED);
        if (WIFEXITED(status) == true){
            mx_printstr("\nFINESHED\n");
            sleep(5);
        }
        if (status != 4735) {
            mx_pid_pop_front(&ppids);
            trig->pids = ppids;
        }
    }
}

void mx_builtin_fg(char **arr, t_trig *trig) {
    int i = 1;
    int j = 1;
    t_pid *ppids = trig->pids;
    t_fg *fg = (t_fg *)malloc(sizeof(t_fg));

///////////////////////////////////////////////////////////
    if (trig->pids != NULL) {
        t_pid *p1 = trig->pids;
        mx_printstr("\n----------BULO----------\n");
        while (p1) {
            mx_printint(i++);
            mx_printchar('\t');
            mx_printstr(p1->name_of_pid[0]);
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
        memset(fg, 0, sizeof(t_fg));
        if (arr[i][0] == '%') {
            char *res = strdup(&arr[i][1]);
            mx_parsing_4_fg(res, fg);
            if (trig->pids != NULL) {
                //j = mx_check_list_4_fg(res, ppids, fg);
                //////////////////////////
                while (ppids != NULL) {
                    if (fg->num) {
                        if (j == mx_atoi(res)) {
                            fg->cont = 1;
                            break;
                        }
                    }
                    else if (fg->str && strstr(ppids->name_of_pid[0], res)) {
                        if (strcmp(res, strstr(ppids->name_of_pid[0], res)) == 0) {
                            fg->cont = 1;
                            break;
                        }
                    }
                    ppids = ppids->next;
                    j++;
                }
                //////////////////////////
                mx_printstr(ppids->name_of_pid[0]);   
                if (!vykonannya(ppids, trig, fg, j)) {
                    mx_printerr("fg: ");
                    mx_printerr(arr[i]);
                    mx_printerr(": no such job\n");
                    trig->err = 1;
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
            trig->err = 1;
        }
    }
    else
        bez_umovy(ppids, trig);





    ///////////////////////////////////////////////////////////
    i = 1;
    if (trig->pids != NULL) {
        t_pid *p2 = trig->pids;
        mx_printstr("\n----------STALO---------\n");
        while (p2) {
            mx_printint(i++);
            mx_printchar('\t');
            mx_printstr(p2->name_of_pid[0]);
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
