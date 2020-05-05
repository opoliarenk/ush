#include "../inc/ush.h"

char **mx_delim_space(char *line) {
    char **mass = malloc(sizeof(char*) * mx_countingw(line) + 1);
    int j_k_c_ko[4] = {0, 0, 0, 0};
    int len = strlen(line);

    mx_new_malloc(mass, line);
    for (int i = 0; i < len; i++) {
        if (line[i] == '\\' && line[i + 1] == '\\' && mx_check_for_echoE(line) != true) { ///// HEHEHEHEH
            while (line[i] == '\\') {
                mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                j_k_c_ko[1]++;
                i++;
                while (j_k_c_ko[2] != 3 && line[i] == '\\') {
                    j_k_c_ko[2]++;
                    i++;
                }
                j_k_c_ko[2] = 0;
            }
        } ///// HEHEHEHEHE
        if (line[i] == '\\') { 
            i++;
        } 
        if (line[i] == '\'') {
            mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];//del
            j_k_c_ko[1]++;//del
            i++;
            while (line[i] != '\'') {
                if (line[i] == '\\' && line[i + 1] == '\\' && mx_check_for_echoE(line) != true) { /////
                    while (line[i] == '\\') {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                        j_k_c_ko[1]++;
                        i++;
                        while (j_k_c_ko[2] != 1 && line[i] == '\\') {
                            j_k_c_ko[2]++;
                            i++;
                        }
                        j_k_c_ko[2] = 0;
                    }
                } /////
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) //here
                    i++;
                if (line[i] == '\'') {
                    mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                    j_k_c_ko[1]++;
                    i++;
                    break;
                }
                mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                j_k_c_ko[1]++;
                i++;
                if (line[i + 1] == '\0') {
                    mass[j_k_c_ko[0]][j_k_c_ko[1]] = '\0';
                    break;
                }
            }
        }
        if (line[i] == '`') {
            mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];//del
            j_k_c_ko[1]++;//del
            i++;
            while (line[i] != '`') {
                if (line[i] == '\\' && line[i + 1] == '\\' && mx_check_for_echoE(line) != true) { /////
                    while (line[i] == '\\') {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                        j_k_c_ko[1]++;
                        i++;
                        while (j_k_c_ko[2] != 1 && line[i] == '\\') {
                            j_k_c_ko[2]++;
                            i++;
                        }
                        j_k_c_ko[2] = 0;
                    }
                } 
                if (line[i] == '`') {
                    mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                    j_k_c_ko[1]++;
                    i++;
                    break;
                }
                mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                j_k_c_ko[1]++;
                i++;
                if (line[i + 1] == '\0') {
                    mass[j_k_c_ko[0]][j_k_c_ko[1]] = '\0';
                    break;
                }
            }
        }
        if (line[i] == '$' && line[i + 1] == '(') {
            mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];//del
            j_k_c_ko[1]++;//del
            i++;
            j_k_c_ko[3]++;
            while(j_k_c_ko[3] != 0) {//line[i] != ')'
                if (line[i] == '\\' && line[i + 1] == '\\' && mx_check_for_echoE(line) != true) { /////
                    while (line[i] == '\\') {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                        j_k_c_ko[1]++;
                        i++;
                        while (j_k_c_ko[2] != 3 && line[i] == '\\') {
                            j_k_c_ko[2]++;
                            i++;
                        }
                        j_k_c_ko[2] = 0;
                    }
                } /////
                else {
                    if (line[i] == '$' && line[i + 1] == '(')
                        j_k_c_ko[3]++;
                    if (line[i] == ')')
                        j_k_c_ko[3]--;
                    if (j_k_c_ko[3] == 0 && line[i] == ')') {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                    }
                    else {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                        j_k_c_ko[1]++;
                        i++;
                    }
                }
                if (!line[i])
                    break;
            }
        }
        if (line[i] == '\"') {
            mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];//del
            j_k_c_ko[1]++;//del
            i++;
            while (line[i] != '\"') { 
                if (line[i] == '\\' && line[i + 1] == '\\' && mx_check_for_echoE(line) != true) { /////
                    while (line[i] == '\\') {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                        j_k_c_ko[1]++;
                        i++;
                        while (j_k_c_ko[2] != 3 && line[i] == '\\') {
                            j_k_c_ko[2]++;
                            i++;
                        }
                        j_k_c_ko[2] = 0;
                    }
                } /////
                if (line[i] == '$' && line[i + 1] == '(') {
                    while (line[i] != ')') {
                        mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                        j_k_c_ko[1]++;
                        i++;
                    }
                }
                if (line[i] == '\"') {
                    break;
                }
                if (line[i] == '\\' && (line[i + 1] == '\"' || line[i + 1] == '`')) 
                    i++;
                if (!line[i])
                    break;
                mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                j_k_c_ko[1]++;
                i++;
            }
            // mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];//del
            // j_k_c_ko[1]++;//del
            // i++;
            if (line[i] == '\0') {
                j_k_c_ko[0]++;
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
                    mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
                }
                j_k_c_ko[0]++;
                j_k_c_ko[1] = 0;
        }
        else {
            mass[j_k_c_ko[0]][j_k_c_ko[1]] = line[i];
            j_k_c_ko[1]++;
        }
    }
    mass[j_k_c_ko[0]] = NULL;
    return mass;
}

