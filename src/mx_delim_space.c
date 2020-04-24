#include "../inc/ush.h"

char **mx_delim_space(char *line) {
    char **mass = malloc(sizeof(char*) * mx_countingw(line) + 1);
    int j = 0;
    int k = 0;
    int len = strlen(line);
    int counter = 0;
    int kol = 0;

    mx_new_malloc(mass, line);
    for (int i = 0; i < len; i++) {
        if (line[i] == '\\' && line[i + 1] == '\\') { ///// HEHEHEHEH
            while (line[i] == '\\') {
                mass[j][k] = line[i];
                k++;
                i++;
                while (counter != 3 && line[i] == '\\') {
                    counter++;
                    i++;
                }
                counter = 0;
            }
        } ///// HEHEHEHEHE
        if (line[i] == '\'') {
            mass[j][k] = line[i];//del
            k++;//del
            i++;
            while (line[i] != '\'') {
                if (line[i] == '\\' && line[i + 1] == '\\') { /////
                    while (line[i] == '\\') {
                        mass[j][k] = line[i];
                        k++;
                        i++;
                        while (counter != 1 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                } /////
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) //here
                    i++;
                if (line[i] == '\'') {
                    mass[j][k] = line[i];
                    k++;
                    i++;
                    break;
                }
                mass[j][k] = line[i];
                k++;
                i++;
                if (line[i + 1] == '\0') {
                    mass[j][k] = '\0';
                    break;
                }
            }
        }
        if (line[i] == '`') {
            mass[j][k] = line[i];//del
            k++;//del
            i++;
            while (line[i] != '`') {
                if (line[i] == '\\' && line[i + 1] == '\\') { /////
                    while (line[i] == '\\') {
                        mass[j][k] = line[i];
                        k++;
                        i++;
                        while (counter != 1 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                } /////
                // if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) //here
                //     i++;
                if (line[i] == '`') {
                    mass[j][k] = line[i];
                    k++;
                    i++;
                    break;
                }
                mass[j][k] = line[i];
                k++;
                i++;
                if (line[i + 1] == '\0') {
                    mass[j][k] = '\0';
                    break;
                }
            }
        }
        if (line[i] == '$' && line[i + 1] == '(') {
            mass[j][k] = line[i];//del
            k++;//del
            i++;
            kol++;
            while(kol != 0) {//line[i] != ')'
                if (line[i] == '\\' && line[i + 1] == '\\') { /////
                    while (line[i] == '\\') {
                        mass[j][k] = line[i];
                        k++;
                        i++;
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
                        mass[j][k] = line[i];
                    }
                    else {
                        mass[j][k] = line[i];
                        k++;
                        i++;
                    }
                }
                if (!line[i])
                    break;
            }
        }
        if (line[i] == '\"') {
            mass[j][k] = line[i];//del
            k++;//del
            i++;
            while (line[i] != '\"') { 
                if (line[i] == '\\' && line[i + 1] == '\\') { /////
                    while (line[i] == '\\') {
                        mass[j][k] = line[i];
                        k++;
                        i++;
                        while (counter != 3 && line[i] == '\\') {
                            counter++;
                            i++;
                        }
                        counter = 0;
                    }
                } /////
                if (line[i] == '$' && line[i + 1] == '(') {
                    while (line[i] != ')') {
                        mass[j][k] = line[i];
                        k++;
                        i++;
                    }
                }
                if (line[i] == '\"') {
                    break;
                }
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) //here
                    i++;
                if (!line[i])
                    break;
                mass[j][k] = line[i];
                k++;
                i++;
            }
            mass[j][k] = line[i];//del
            k++;//del
            i++;
            if (line[i] == '\0') {
                j++;
                break;
            }
        }
        if (line[i] == ' ' || line[i] == '\t' 
            || line[i] == '\r' || line[i] == '\n' 
            || line[i] == '\a' || line[i + 1] == '\0') {
                while (line[i + 1] == ' ' || line[i + 1] == '\t' 
                    || line[i + 1] == '\r' || line[i + 1] == '\n' 
                    || line[i + 1] == '\a')
                        i++;
                if (line[i + 1] == '\0' && line[i] != ' ' && line[i] != '\t' 
                    && line[i] != '\r' && line[i] != '\n' 
                    && line[i] != '\a') {
                    mass[j][k] = line[i];
                }
                j++;
                k = 0;
        }
        else {
            mass[j][k] = line[i];
            k++;
        }
    }
    mass[j] = NULL;
    return mass;
}

