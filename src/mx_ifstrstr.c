#include "../inc/ush.h"

static bool is_alpha(char c) {
    if ((c >= 65 && c <= 90) 
     || (c >= 97 && c <= 122))
        return true;
    else
        return false;
}

bool mx_ifstrstr(const char *haystack, const char *needle) {
    int i = 0;
    int j = 0;
    int size_of_needle = strlen(needle);
    int size_of_haystack = strlen(haystack);
    bool mozhna = false;

    while(i < size_of_haystack) {
        if (!is_alpha(haystack[i - 1]) && is_alpha(haystack[i]) && !mozhna)
            mozhna = true;
        if (is_alpha(haystack[i - 1]) && !is_alpha(haystack[i]) && mozhna)
            mozhna = false;
        if (mozhna) {
            while(strcmp(&haystack[i], &needle[j]) == 0) {
                j++;
            }
        }
        if(j == size_of_needle) {
            return true;
        }
        i++;
    }
    return false;
}
