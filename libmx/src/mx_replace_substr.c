#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
	int p = 0;
	int k = 0;
	int s = 0;
	int l = 0;
	int ok = 0;
	int count = 0;

	if(str == NULL || sub == NULL || replace == NULL) {
		return NULL;
	} else {
		int lenstr = mx_strlen(str);
		int lensub = mx_strlen(sub);
		int lenreplace = mx_strlen(replace);
		int csub = mx_count_substr(str, sub);

		char *new = mx_strnew(lenstr - (csub * lensub) + (csub * lenreplace));

		for(int i = 0; i < lenstr - (csub * lensub) + (csub * lenreplace); i++) {
			if(str[k] == sub[s]) {
				l = k;
				for(; s < lensub; l++) {
					if(str[l] == sub[s]) {
						count++;
					}
					s++;
				}
			}
			if(count == lensub) {
				while(p < lenreplace) {
					new[i] = replace[p];
					p++;
					i++;
				}
				while(ok < lensub) {
					k++;
					ok++;
				}
				ok = 0;
				i--;
			} else {
				new[i] = str[k];
				k++;
			}
			s = 0;
			p = 0;
			count = 0;

		}
		return new;
	}
return NULL;
	}
