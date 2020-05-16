#include "../inc/ush.h"

static void helper2(int *i, int *j_e_k) {
    j_e_k[0]++;
    (*i)++;
}

static void helper1(char *line, int *i, int *j_e_k) {
    int counter = 0;

    if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' 
        && mx_check_for_echoE(line) != true) {
        while (line[(*i)] == '\\') {
            (*i)++;
            j_e_k[0]++;
            while (counter != 1 && line[(*i)] == '\\') {
                counter++;
                (*i)++;
            }
            counter = 0;
        }
    }
}

static void helper3(int *i, int *j_e_k) {
    (*i) = (*i) + 2;
    j_e_k[0]++;
}

static void helper4(int *j_e_k, char ***mass) {
    j_e_k[0]++;
    (*mass)[j_e_k[1]] = mx_strnew(j_e_k[0]);
}

void mx_new_m_help(char *line, char ***mass, int *j_e_k, int *i) {
    if (line[(*i)] == '\'' && line[(*i) - 1] != '\\') {
        helper2(i, j_e_k);
        while (line[(*i)] != '\'') {
            helper1(line, i, j_e_k);
            if (line[(*i)] == '\\' 
                && (line[(*i) + 1] == '\"' || line[(*i) + 1] == '`')) 
                helper3(i, j_e_k);
            else {
                if (line[(*i) + 1] == '\0') {
                    helper4(j_e_k, mass);
                    break;
                } 
                if (line[(*i)] == '\'') {
                    helper2(i, j_e_k);
                    break;
                }
                helper2(i, j_e_k);
            }
        }
    }
}

