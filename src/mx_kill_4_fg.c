#include "../inc/ush.h" 

bool mx_kill_4_fg(t_pid *ppids, t_trig **trig, t_fg *fg, int j) {
    int status;
    t_pid *p = (*trig)->pids;

    if (fg->cont) {
        if (ppids) {
            mx_printname_4_fg(ppids);
            kill(ppids->npid, SIGCONT);
            waitpid(ppids->npid, &status, WUNTRACED);
            if (status != 4735) {
                mx_pop_specific_4_pids(&p, j - 1);
                (*trig)->pids = p;
            }
        }
    }
    else
        return false;
    return true;
}
