#include "../inc/ush.h"

static void helper1(int *i, int *j_e_k) {
    (*i)++;
    j_e_k[0]++;
}

static void helper2(char *line, int *j_e_k, int *i) {
    int counter = 0;

    if (line[(*i)] == '\\' 
        && line[(*i) + 1] == '\\' && mx_check_for_echoE(line) != true) { 
        while (line[(*i)] == '\\') {
            helper1(i, j_e_k);
            while (counter != 3 && line[(*i)] == '\\') {
                counter++;
                (*i)++;
            }
            counter = 0;
        }
    } 
    if (line[(*i)] == '$' && line[(*i) + 1] == '(') 
        while (line[(*i)] != ')') 
            helper1(i, j_e_k); 
}

static void helper3(int *i, int *j_e_k) {
    (*i) = (*i) + 2;
    j_e_k[0]++;
}

void mx_new_str_d(char *line, char ***mass, int *j_e_k, int *i) {
    if (line[(*i)] == '\"') {
        helper1(i, j_e_k);
        while (line[(*i)] != '\"') { 
            helper2(line, j_e_k, i);
            if (line[(*i)] == '\\' 
                && (line[(*i) + 1] == '\"' || line[(*i) + 1] == '`'))
                helper3(i, j_e_k);
            else {
                if (line[(*i)] == '\"') { 
                    helper1(i, j_e_k);
                    break;
                } 
                helper1(i, j_e_k);
            }
            if (!line[(*i)]) {
                (*mass)[j_e_k[1]] = mx_strnew(j_e_k[0]);
                break;
            }
        }
    }
}

