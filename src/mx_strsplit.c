#include "../inc/ush.h"

int mx_while_delim(const char *str, int i, char c) {
	while(str[i] == c) {
  		i++;
 	}
	return i;
}

char **mx_strsplit(const char *s, char c) {
	int i;
	int k = 0;
	int j = 0;
	int g;
	int l = 0;

	if (s == NULL) {
		return NULL;
 	}
 	i = mx_count_words(s, c);
 	char **arr = malloc (sizeof (char *) * (i + 1));
 	for (int I = 0; I < i; I++){
  		l = mx_while_delim(s, l, c);
  		g = l;
  		while(s[l] != c && s[l] != '\0') {
   			l++;
  		}
  		j = l - g;
  		arr[k] = malloc(j + 1);
  		arr[k][j] = 0;
  		mx_strncpy(arr[k], (char *) &s[g], j );
  		k++;
  		l++;
 	}
 	arr[k] = 0;

    return arr;
}
