#include "../inc/ush.h"

static int redirectin(char **mass, t_trig *trig) {
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], ">") == 0)
            posi = mx_redir(mass, trig); 
    return posi;
}

static int redirectout(char **mass, t_trig *trig) {
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], "<") == 0)
            posi = mx_redirout(mass, trig); 
    return posi;
}

// static int both(char **mass, t_trig *trig) {
//     int posi = 2;
//     int in = 0;
//     int out = 0;

//     for (int i = 0; mass[i] != NULL; i++) {
//         if ((strcmp(mass[i], ">") == 0)
//             in = 1; 
//         if ((strcmp(mass[i], "<") == 0)
//             out = 1;
//     }
//     if (in == 1 && out == 1) {
//         // posi = ...функа на два одновременно

//     }
//     return posi;
// }

// static int err_stream(char **mass, t_trig *trig) на поток ошибок 
//     int posi = 2;

//     for (int i = 0; mass[i] != NULL; i++) {
//         if (strcmp(mass[i], "2") == 0 && strcmp(mass[i + 1], ">") == 0)
//             posi = ; 
//     return posi;
// }

int mx_red_pipe(char **mass, t_trig *trig) { //  проверяет или есть редирекшены , сначала или их не два одновременно, а потом каждый по отдельности 
    int redirin; 
    int redirout; 
    
    if ((redirin = redirectin(mass, trig)) != 2) 
        return redirin;
    if ((redirout = redirectout(mass, trig)) != 2)
        return redirout;
    return 2;
}
