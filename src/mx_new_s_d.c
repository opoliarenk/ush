#include "../inc/ush.h"

static void helpp(char *line, int *j_e_k, int *i) {
    if (line[(*i)] == '$' && line[(*i) + 1] == '(')
        j_e_k[2]++;
    if (line[(*i)] == ')')
        j_e_k[2]--;
    if (j_e_k[2] == 0 && line[(*i)] == ')') {
    }
    else {
        j_e_k[0]++;
        (*i)++;
    }
}

static void helper1(char *line, int *i, int *j_e_k) {
    int counter = 0;

    while (line[(*i)] == '\\') {
        (*i)++;
        j_e_k[0]++;
        while (counter != 3 && line[(*i)] == '\\') {
            counter++;
            (*i)++;
        }
        counter = 0;
    }
}

void mx_new_s_d(char *line, char ***mass, int *j_e_k, int *i) {
    if (line[(*i)] == '$' && line[(*i) + 1] == '(') {
        (*i)++;
        j_e_k[0]++;
        j_e_k[2]++;
        while(j_e_k[2] != 0) {
            if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' 
                && mx_check_for_echoE(line) != true) { 
                helper1(line, i, j_e_k);
            } 
            else {
                helpp(line, j_e_k, i);
            }
            if (!line[(*i)]) {
                (*mass)[j_e_k[1]] = mx_strnew(j_e_k[0]);
                break;
            }
        }
    }
}

