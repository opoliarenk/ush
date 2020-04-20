#include "../inc/ush.h"

static void creating(char **mass) {
    if (!mass) 
        return;
}

static void counting_subs(char **mass) {
    int comm_count = 0;
    int j = 0;

    for (int i = 0; mass[i]; i++) {
        if (strcmp(mass[i], "`") == 0)
            comm_count++;
        else if (strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0)
            comm_count += 2;
    }
    comm_count /= 2;
    for (; comm_count > 0; comm_count--) {
        for (int i = 0; mass[i]; i++) {
            if (strcmp(mass[i], "`") == 0 || (strcmp(mass[i], "$") == 0 && strcmp(mass[i + 1], "(") == 0))
                j++;
            if (j == comm_count) {
                creating(&mass[i]);
            }
        }
        j = 0;
    }
}

void mx_subspars(char **mass) {
    counting_subs(mass);
}

