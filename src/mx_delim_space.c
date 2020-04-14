#include "../inc/ush.h"

static void mallocingstr(char **mass, char *line) {
    int j = 0;
    int elem = 0;
    int len = strlen(line);
    int counter = 0;

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
            //j = j + 2;//delete
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
                    j++;
                    i++;
                }
            }
        } //////// TROUBLE
        if (line[i] == '\"') {
            i++;
            //j = j + 2;//delete
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
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) {
                    i = i + 2;
                    j++;
                } 
                else {
                    j++;
                    i++;
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

static int count_words(char *line) {
    int len = strlen(line);
    int countw = 0;

    for (int i = 0; i < len; i++) {
        if (line[i] == '\"') {
            i++;
            while (line[i] != '\"') { 
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) { //here
                    i++;
                }
                i++;
            }
        }  
        if (line[i] == ' ' || line[i] == '\t' 
            || line[i] == '\r' || line[i] == '\n' 
            || line[i] == '\a' || line[i + 1] == '\0') {
                while (line[i + 1] == ' ' || line[i + 1] == '\t' 
                    || line[i + 1] == '\r' || line[i + 1] == '\n' 
                    || line[i + 1] == '\a')
                        i++;
                countw++;
        }
    }
    return countw;
}

char **mx_delim_space(char *line) {
    int count = count_words(line);
    char **mass = malloc(sizeof(char*) * count + 1);
    int j = 0;
    int k = 0;
    int len = strlen(line);
    int counter = 0;
    
    mallocingstr(mass, line);
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
                mass[j][k] = line[i];
                k++;
                i++;
            }
            mass[j][k] = line[i];//del
            k++;//del
            i++;
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
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) //here
                    i++;
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
                if (line[i + 1] == '\0') {
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

