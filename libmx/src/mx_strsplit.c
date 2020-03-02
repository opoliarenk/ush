#include "../inc/libmx.h"

static int cheker(const char *s, char c) {
	int i = 0;
	int flag = 0;

	while (s[i] != '\0') {
		if (s[i] != c)
			flag = 1;
		i++;
	}
	return flag;
}

char **mx_strsplit(const char *s, char c) {
    char **res;
    char *extra;
    int i = -1;
    int a = 0;
    int count = 0;

    if (s == NULL)
        return NULL;
    if (!cheker(s, c))
		return NULL;
	extra = mx_ultra_del_extra_spaces(s, c);
    res = (char **)malloc((mx_count_words(s, c) + 1) * sizeof(char **));
    while (extra[++i])
        if (extra[i] == c || extra[i + 1] == '\0') {
            res[a++] = mx_strndup(&extra[count], (i - count));
            count = i + 1;
        }
    res[a] = NULL;
    mx_strdel(&extra);
    return res;
}
