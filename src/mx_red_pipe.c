#include "../inc/ush.h"

static int redirectin(char **mass) {
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], ">") == 0)
            posi = mx_redir(mass); // работает но назара функи надо!! strcmp(mass[i], "<") == 0)
    return posi;
}

static int redirectout(char **mass) {
    int posi = 2;

    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(mass[i], "<") == 0)
            posi = mx_redirout(mass); // работает но назара функи надо!! strcmp(mass[i], "<") == 0)
    return posi;
}

// static int both(char **mass) {
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

int mx_red_pipe(char **mass) { //  проверяет или есть редирекшены , сначала или их не два одновременно, а потом каждый по отдельности 
    int redirin; 
    int redirout; 
   // int bothper;

    // if (bothper = both(mass) != 2)
    //     return bothper;
    if ((redirin = redirectin(mass)) != 2) 
        return redirin;
    if ((redirout = redirectout(mass)) != 2)
        return redirout;
    return 2;
}
