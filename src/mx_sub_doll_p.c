#include "../inc/ush.h"

static void helper(char *line, int *i, int *j_k_c_ko, char ***mass) {
    (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
    j_k_c_ko[1]++;
    (*i)++;
}

static void helper2(char *line, int *i, int *j_k_c_ko, char ***mass) {
    while (line[(*i)] == '\\') {
        helper(line, i, j_k_c_ko, mass);
        while (j_k_c_ko[2] != 3 && line[(*i)] == '\\') {
            j_k_c_ko[2]++;
            (*i)++;
        }
        j_k_c_ko[2] = 0;
    }
}

static void helper3(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '$' && line[(*i) + 1] == '(')
        j_k_c_ko[3]++;
    if (line[(*i)] == ')')
        j_k_c_ko[3]--;
    if (j_k_c_ko[3] == 0 && line[(*i)] == ')') {
        (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
    }
    else {
        helper(line, i, j_k_c_ko, mass);
    }
}

void mx_sub_doll_p(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '$' && line[(*i) + 1] == '(') {
        helper(line, i, j_k_c_ko, mass);
        j_k_c_ko[3]++;
        while(j_k_c_ko[3] != 0) {
            if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' && mx_check_for_echoE(line) != true) { 
                helper2(line, i, j_k_c_ko, mass);
            } 
            else {
                helper3(line, i, j_k_c_ko, mass);
            }
            if (!line[(*i)])
                break;
        }
    }    
}
