#include "../inc/ush.h"

void mx_new_malloc(char **mass, char *line) {
    int j = 0;
    int elem = 0;
    int len = strlen(line);
    int counter = 0;
    int kol = 0;

    for (int i = 0; i < len; i++) {
        if (line[i] == '\\' && line[i + 1] == '\\') { ///// HEHEHEHE
                    while (line[i] == '\\') {
                        i++;
                        j++;
                        while (counter != 3 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                } ///// HEHEHHE
        if (line[i] == '\'') { ////// TROUBLE
            i++;
            j++;
            while (line[i] != '\'') {
                if (line[i] == '\\' && line[i + 1] == '\\') {
                    while (line[i] == '\\') {
                        i++;
                        j++;
                        while (counter != 1 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                }
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) {
                    i = i + 2;
                    j++;
                } 
                else {
                    if (line[i + 1] == '\0') {
                        j++;
                        mass[elem] = mx_strnew(j);
                        break;
                    } 
                    if (line[i] == '\'') {
                        j++;
                        i++;
                        break;
                    }
                    j++;
                    i++;
                }
            }
        } //////// TROUBLE/////NEW
         if (line[i] == '`') { ////// TROUBLE
            i++;
            j++;
            while (line[i] != '`') {
                if (line[i] == '\\' && line[i + 1] == '\\') {
                    while (line[i] == '\\') {
                        i++;
                        j++;
                        while (counter != 1 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                }
                else {
                    if (line[i + 1] == '\0') {
                        j++;
                        mass[elem] = mx_strnew(j);
                        break;
                    } 
                    if (line[i] == '`') {
                        j++;
                        i++;
                        break;
                    }
                    j++;
                    i++;
                }
            }
        } //////// TROUBLE NEW
        if (line[i] == '$' && line[i + 1] == '(') {
            i++;
            j++;
            kol++;
            while(kol != 0) {//line[i] != ')'
                if (line[i] == '\\' && line[i + 1] == '\\') { /////
                    while (line[i] == '\\') {
                        i++;
                        j++;
                        while (counter != 3 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                } /////
                else {
                    if (line[i] == '$' && line[i + 1] == '(')
                        kol++;
                    if (line[i] == ')')
                        kol--;
                    if (kol == 0 && line[i] == ')') {
                    }
                    else {
                        j++;
                        i++;
                    }
                }
                if (!line[i]) {
                    mass[elem] = mx_strnew(j);
                    break;
                }
            }
        }
        if (line[i] == '\"') {
            i++;
            j++;
            while (line[i] != '\"') { 
                if (line[i] == '\\' && line[i + 1] == '\\') { /////
                    while (line[i] == '\\') {
                        i++;
                        j++;
                        while (counter != 3 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                } /////
                if (line[i] == '$' && line[i + 1] == '(') {
                    while (line[i] != ')') {
                        i++;
                        j++;
                    }
                }
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) {
                    i = i + 2;
                    j++;
                } 
                else {
                    if (line[i] == '\"') { //////////
                        j++;
                        i++;
                        break;
                    }
                    j++;
                    i++;
                }
                if (!line[i]) {
                    mass[elem] = mx_strnew(j);
                    break;
                }
            }
        }
        if (line[i] == ' ' || line[i] == '\t' 
            || line[i] == '\r' || line[i] == '\n'
            || line[i] == '\a' || line[i + 1] == '\0') { //|| line[i + 1] == '\0'
                if (line[i + 1] == '\0')
                    j++;
                while (line[i + 1] == ' ' || line[i + 1] == '\t' 
                    || line[i + 1] == '\r' || line[i + 1] == '\n'
                    || line[i + 1] == '\a') 
                        i++;
                mass[elem] = mx_strnew(j);
                elem++;
                j = 0;
        }
        else {
            j++;
        }
    }
}

