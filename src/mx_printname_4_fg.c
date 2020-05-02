#include "../inc/ush.h" 

void mx_printname_4_fg(t_pid *ppids) {
    int i = 0;

    while (ppids->name_of_pid[i + 1]) {
        mx_printstr(ppids->name_of_pid[i]);
        mx_printchar(' ');
        i++;
    }
    mx_printstr(ppids->name_of_pid[i]);
    mx_printchar(10);
}
