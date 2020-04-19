#include "../inc/ush.h"

static char **creating(char **mass) {
    char **buff = NULL;
    int count = 0;
    char *in_mass = NULL;

    for(int i = 0; mass[i]; i++) {
        if (strcmp(mass[i],"`") == 0) {
            i++;
            while(strcmp(mass[i],"`") != 0)
                count++;
        }
        if (mass[i][0] == '\"') {
            in_mass = mx_strstr(mass[0], "`");
        }
    }
    if (count > 0) //ESLI DA, TO SOZDAEM MASSIV
    if (in_mass != NULL) //Esli ne ukazivaet na NULL, tipa chto nashli v stroke `

}

void mx_subspars(char **mass) {
   

}

