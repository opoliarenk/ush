#include "../inc/ush.h"

int mx_hardparser(char *line) {
    char *newl = mx_hardsplit(line); //FREE
    char **mass = mx_sh_splite(newl); //FREE

    for (int i = 0; mass[i]; i++) //testing
        printf("%s\n", mass[i]);


    if (mx_red_pipe(mass) == 2) {
        //exit(0);    //функа назара      
        //printf("HELLO");  
    }
    return 1; // временно
}
