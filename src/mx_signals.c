#include "../inc/ush.h"

static void sigcatch(int sig) {
    mx_printstr("\nsig catch ");
    mx_printint(sig);
    mx_printchar(10);
}


void mx_signals() {
	signal(SIGTSTP, sigcatch);
    signal(SIGINT, sigcatch);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    //signal(SIGSEGV, sigcatch);
}
