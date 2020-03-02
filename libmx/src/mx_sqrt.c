#include "../inc/libmx.h"

int mx_sqrt(int x) {
    int i;

    i = 1;
    while (i < x) {
        if (i * i == x)
            return i;
        i++;
    }
    return 0;
}
