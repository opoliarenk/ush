#include "../inc/ush.h"

static void helper(char *line, int *i, int *j_k_c_ko, char ***mass) {
    (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
    j_k_c_ko[1]++;
    (*i)++;
}

static void helper2(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' && mx_check_for_echoE(line) != true) { /////
        while (line[(*i)] == '\\') {
            helper(line, i, j_k_c_ko, mass);
            while (j_k_c_ko[2] != 3 && line[(*i)] == '\\') {
                j_k_c_ko[2]++;
                (*i)++;
            }
            j_k_c_ko[2] = 0;
        }
    } 
    if (line[(*i)] == '$' && line[(*i) + 1] == '(') {
        while (line[(*i)] != ')') {
            helper(line, i, j_k_c_ko, mass);
        }
    }
}

void mx_doubl_d(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '\"') {
        helper(line, i, j_k_c_ko, mass);
        while (line[(*i)] != '\"') { 
            helper2(line, i, j_k_c_ko, mass);
            if (line[(*i)] == '\"')
                break;
            if (line[(*i)] == '\\' 
                && (line[(*i) + 1] == '\"' || line[(*i) + 1] == '`')) 
                (*i)++;
            if (!line[(*i)])
                break;
            helper(line, i, j_k_c_ko, mass);
        }
    }
}

