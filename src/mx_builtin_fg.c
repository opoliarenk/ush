#include "../inc/ush.h" 

static void bez_umovy(t_pid *ppids, t_trig **trig) {
    int status;
    t_pid *p = (*trig)->pids;

    if (ppids) {
        mx_printname_4_fg(ppids);
        kill(ppids->npid, SIGCONT);
        waitpid(ppids->npid, &status, WUNTRACED);
        if (status != 4735) {
            mx_pid_pop_front(&p);
            (*trig)->pids = p;
        }
    }
}

static void part1(char **arr, t_trig *trig, t_pid *ppids, t_fg *fg) {
    int j = 1;
    int i = 1;
    char *res = strdup(&arr[i][j]);

    mx_parsing_4_fg(res, fg);
    if (trig->pids != NULL) {
        j = mx_check_list_4_fg(res, &ppids, fg); 
        if (!mx_kill_4_fg(ppids, &trig, fg, j)) {
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

static void part2(char **arr, t_trig *trig, t_pid *ppids, t_fg *fg) {
    int j = 1;
    int i = 1;

    fg->str = 1;
    fg->num = 0;
    if (trig->pids != NULL) {
        j = mx_check_list_4_fg(arr[i], &ppids, fg); 
        if (!mx_kill_4_fg(ppids, &trig, fg, j)) {
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
}

void test1(t_trig *trig);
void test2(t_trig *trig);

void mx_builtin_fg(char **arr, t_trig *trig) {
    int i = 1;
    t_pid *ppids = trig->pids;
    t_fg *fg = (t_fg *)malloc(sizeof(t_fg));

    if (arr[1]) {
        if (strcmp(arr[1], "show") == 0)
        test1(trig);
    }

    if (arr[i]) {
        memset(fg, 0, sizeof(t_fg));
        if (arr[i][0] == '%')
            part1(arr, trig, ppids, fg);
        else
            part2(arr, trig, ppids, fg);
    }
    else
        bez_umovy(ppids, &trig);

    if (arr[1]) {
        if (strcmp(arr[1], "show") == 0)
            test2(trig);
    }
}

void test1(t_trig *trig) {
    int i = 1;

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
}

void test2(t_trig *trig) {
    int i = 1;

    if (trig->pids != NULL) {
        t_pid *p1 = trig->pids;
        mx_printstr("\n----------STALO----------\n");
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
}
