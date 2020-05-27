#include "../inc/ush.h"

static void helper(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' 
        && mx_check_for_echoE(line) != true) { 
        while (line[(*i)] == '\\') {
            (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
            j_k_c_ko[1]++;
            (*i)++;
            while (j_k_c_ko[2] != 1 && line[(*i)] == '\\') {
                j_k_c_ko[2]++;
                (*i)++;
            }
            j_k_c_ko[2] = 0; 
        }
    } 
}

static void helper2(char *line, int *i, int *j_k_c_ko, char ***mass) {
    (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
    j_k_c_ko[1]++;
    (*i)++;
}

void mx_sky_doubt(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '\'') {
        helper2(line, i, j_k_c_ko, mass);
        while (line[(*i)] != '\'') {
            helper(line, i, j_k_c_ko, mass);
            if (line[(*i)] == '\\' &&
                (line[(*i) + 1] == '\"' || line[(*i) + 1] == '`')) 
                (*i)++;
            if (line[(*i)] == '\'') {
                helper2(line, i, j_k_c_ko, mass);
                break;
            }
            helper2(line, i, j_k_c_ko, mass);
            if (line[(*i) + 1] == '\0') {
                (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = '\0';
                break;
            }
        }
    }
}

