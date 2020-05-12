#include "../inc/ush.h"

static void helper1(int *i, int *j_e_k) {
    (*i)++;
    j_e_k[0]++;
}

static void helper2(char *line, int *i, int *j_e_k) {
    int counter = 0;

    while (line[(*i)] == '\\') {
        helper1(i, j_e_k);
        while (counter != 1 && line[(*i)] == '\\') {
            counter++;
            (*i)++;
        }
        counter = 0;
    }
} 

void mx_new_m_sd(char *line, char ***mass, int *j_e_k, int *i) {
    if (line[(*i)] == '`' && line[(*i) - 1] != '\\') { 
        helper1(i, j_e_k);
        while (line[(*i)] != '`') {
            if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' 
                && mx_check_for_echoE(line) != true)
                helper2(line, i, j_e_k);
            else {
                if (line[(*i) + 1] == '\0') {
                    j_e_k[0]++;
                    (*mass)[j_e_k[1]] = mx_strnew(j_e_k[0]);
                    break;
                } 
                if (line[(*i)] == '`') {
                    helper1(i, j_e_k);
                    break;
                }
                helper1(i, j_e_k);
            }
        }
    } 
}

