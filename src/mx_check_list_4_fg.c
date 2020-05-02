#include "../inc/ush.h" 

int mx_check_list_4_fg(char *res, t_pid **ppids, t_fg *fg) {
    int j = 1;

    while ((*ppids) != NULL) {
        if (fg->num) {
            if (j == mx_atoi(res)) {
                fg->cont = 1;
                break;
            }
        }
        else if (fg->str && strstr((*ppids)->name_of_pid[0], res)) {
            if (strcmp(res, strstr((*ppids)->name_of_pid[0], res)) == 0) {
                fg->cont = 1;
                break;
            }
        }
        (*ppids) = (*ppids)->next;
        j++;
    }
    return j;
}
