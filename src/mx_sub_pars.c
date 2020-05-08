#include "../inc/ush.h"

static void helper(char *line, int *i, int *j_k_c_ko, char ***mass) {
    (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
    j_k_c_ko[1]++;
    (*i)++;
}

static void helper1(char *line, int *i, int *j_k_c_ko, char ***mass) {
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

void mx_sub_pars(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '`') {
        helper(line, i, j_k_c_ko, mass);
        while (line[(*i)] != '`') {
            helper1(line, i, j_k_c_ko, mass);
            if (line[(*i)] == '`') {
                helper(line, i, j_k_c_ko, mass);
                break;
            }
            helper(line, i, j_k_c_ko, mass);
            if (line[(*i) + 1] == '\0') {
                (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = '\0';
                break;
            }
        }
    }
}
