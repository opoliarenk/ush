#include "../inc/libmx.h"

void mx_del_intarr(int ***arr, int size) {
    free(*arr);
}
