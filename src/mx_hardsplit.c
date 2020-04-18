#include "../inc/ush.h"

static char *hash (char *line) { // for the hash, when they comment something
    int i = 0;
    int flag = 0;
    char *new = NULL;
    
    for (; i < mx_strlen(line); i++) {
        if (i == 0 && line[i] == '\"') {
            i++;
            while (line[i] != '\"' && line[i - 1] != '\\') {
                i++;
            }
        }
        else if (line[i] == '\"' && i == 0) { 
            i++;
            while (line[i] != '\"' && line[i - 1] != '\\') {
                i++;
            }
        } 
        else if (line[i] == '\'' && i == 0) {
            i++;
            while (line[i] != '\'') {
                i++;
            }
        }
        else if (line[i] == '\'' && line[i - 1] != '\\') {
            i++;
            while (line[i] != '\'') {
                i++;
            }
        } else if (line[i] == '#') {
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        new = strndup(line, i - 1);
        return new;
    }
    return NULL;
}

char *mx_hardsplit(char *line) {
    int i;
    int j = 0;
    char *new = NULL;
    int k = 0;
    int flag = 0;
    char *newww = hash(line);
    
    if ( newww != NULL) {
        //free(line);
        line = mx_strdup(newww);
    }//LEAKS
    
    for (i = 0; line[i] != '\0'; i++) {
        if (i != 0) {
            if (line[i] == '\'' && line[i - 1] != '\\') {
                i++;
                while (line[i] != '\'')
                    i++;
            } 
            else if (line[i] == '\"' && line[i - 1] != '\\') {
                i++;
                while (line[i] != '\"') {
                    if (line[i] == '\\')
                        i += 2;
                    else 
                        i++;
                }
            }
            if (line[i] == '2' && line[i + 1] == '>' && line[i - 1] == ' ') {
                 j+=2;
                 i++;
                 continue;
             }
            if (line[i] == '>' 
            || line[i] == '(' || line[i] == ')' || line[i] == '`' || line[i] == '<')  
                j += 2;
        } else {
            if (line[i] == '\"') {
                i++;
                while (line[i] != '\"') {
                    if (line[i] == '\\')
                        i += 2;
                    else 
                        i++;
                }
            }
            else if (line[i] == '\'') {
                i++;
                while(line[i] != '\'')
                    i++;
            }
            if (line[i] == '2' && line[i + 1] == '>') {
                 j+=2;
                 i++;
                 continue;
             }
            if (line[i] == '>' 
            || line[i] == '(' || line[i] == ')' || line[i] == '`' || line[i] == '<')  
                j += 2;
        }
    }
    i = i + j;
    flag = 0;
    new = mx_strnew(i);
    for (int q = 0; q < i; q++) {
        if (k != 0) {
            if (line[k] == '\"' && line[k - 1] != '\\') {
                new[q++] = line[k++];
                while (line[k] != '\"') { 
                    if (line[k] == '\\') {
                        new[q++] = line[k++];
                        new[q++] = line[k++];
                    } 
                    else  {
                        new[q++] = line[k++];
                    }
                }
            }
            else if (line[k] == '\'' && line[k - 1] != '\\') {
                new[q++] = line[k++];
                while (line[k] != '\'')
                    new[q++] = line[k++];
            }
            if (line[k] == '2' && line[k + 1] == '>' && line[k - 1] == ' ') {
                new[q++] = ' ';
                new[q++] = '2';
                new[q++] = '>';
                new[q] = ' ';
                k = k + 2;
                continue;
            }     
        } else {
             if (line[k] == '\"') {
                new[q++] = line[k++];
                while (line[k] != '\"') { 
                    if (line[k] == '\\') {
                        new[q++] = line[k++];
                        new[q++] = line[k++];
                    } 
                    else  {
                        new[q++] = line[k++];
                    }
                }
            }
            else if (line[k] == '\'') {
                new[q++] = line[k++];
                while (line[k] != '\'')
                    new[q++] = line[k++];
            }
            if (line[k] == '2' && line[k + 1] == '>' && line[k - 1] == ' ') {
                new[q++] = ' ';
                new[q++] = '2';
                new[q++] = '>';
                new[q] = ' ';
                k = k + 2;
                continue;
            }     
        }
        if (line[k] == '>'  
         || line[k] == '(' || line[k] == ')' || line[k] == '`' || line[k] == '<') {  
            new[q++] = ' ';
            new[q++] = line[k];
            new[q] = ' ';
            k++;
        } 
        else {
            new[q] = line[k];
            k++;
        }
    }
    new[i] = '\0';
    return new;
}
