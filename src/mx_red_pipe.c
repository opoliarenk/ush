#include "../inc/ush.h"

static int redirectin(char **mass, t_trig *trig) {
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], ">") == 0) {
            posi = mx_redir(mass, trig);
            break;
        } 
    return posi;
}

static int redirectout(char **mass, t_trig *trig) {
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], "<") == 0) {
            posi = mx_redirout(mass, trig);
            break;
        } 
    return posi;
}

static int both(char **mass, t_trig *trig) { // доделать еще 
    int posi = 2;
    int in = 0;
    int out = 0;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0 || strcmp(mass[i], "2>") == 0)
            in = 1; 
        if (strcmp(mass[i], "<") == 0)
            out = 1;
    }
    if (in == 1 && out == 1) 
        posi = mx_redboth(mass, trig); 
    return posi;
 }

static int err_stream(char **mass, t_trig *trig) { //на поток ошибок 
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], "2>") == 0)
            posi = mx_rederr(mass, trig); 
    return posi;
}

int mx_red_pipe(char **mass, t_trig *trig) { //  проверяет или есть редирекшены , сначала или их не два одновременно, а потом каждый по отдельности 
    int redirin; 
    int redirout; 
    int rederr;
    int redboth;
    
    if ((redboth = both(mass, trig)) != 2) 
        return redboth;
    if ((rederr = err_stream(mass, trig)) != 2) 
        return rederr;
    if ((redirin = redirectin(mass, trig)) != 2) 
        return redirin;
    if ((redirout = redirectout(mass, trig)) != 2)
        return redirout;
    return 2;
}
