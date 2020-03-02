#include "../inc/libmx.h"

int mx_is_space(char c) {
    if (c == '\n' || c == '\t' || c == '\v' 
        || c == '\r' || c == '\f' || c == ' ')
        return 1;
    else
        return 0;
}
