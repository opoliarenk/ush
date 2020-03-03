#include "../inc/ush.h"

char **mx_newfor_bults(char **mass) {
    int newlen = 0;
    char **newmass = NULL;
    int j = 0;
    
    for (int i = 0; mass[i] != NULL; i++)
        if (strcmp(">" , mass[i]) != 0)
            newlen++;
    newmass = malloc(sizeof (char *) * newlen);
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(">" , mass[i]) == 0) {
            while (strcmp(">" , mass[i]) == 0)
                i++;
            i++;
        }
        if (mass[i] != NULL)
            newmass[j++] = strdup(mass[i]);
    }
    newmass[newlen - 1] = NULL;
    return newmass;
}
