#include "../inc/ush.h"

static void first_count(char *line, int *i, int *j_e_k) {
    int counter = 0;

    if (line[(*i)] == '\\' && line[(*i) + 1] == '\\' 
        && mx_check_for_echoE(line) != true) { 
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
    if (line[(*i)] == '\\')
        (*i)++;
}

static void mall_delim(char *line, char ***mass, int *j_e_k, int *i) {
    if (line[(*i)] == ' ' || line[(*i)] == '\t' 
        || line[(*i)] == '\r' || line[(*i)] == '\n'
        || line[(*i)] == '\a' || line[(*i) + 1] == '\0') { 
        if (line[(*i) + 1] == '\0')
            j_e_k[0]++;
            while (line[(*i) + 1] == ' ' || line[(*i) + 1] == '\t' 
                || line[(*i) + 1] == '\r' || line[(*i) + 1] == '\n'
                || line[(*i) + 1] == '\a') 
                    (*i)++;
            (*mass)[j_e_k[1]] = mx_strnew(j_e_k[0]);
            j_e_k[1]++;
            j_e_k[0] = 0;
    }
    else {
        j_e_k[0]++;
    }
}

void mx_new_malloc(char **mass, char *line) {
    int j_e_k[3] = {0, 0, 0};
    int len = strlen(line);

    for (int i = 0; i < len; i++) {
        first_count(line, &i, j_e_k);
        mx_new_m_help(line, &mass, j_e_k, &i);
        mx_new_m_sd(line, &mass, j_e_k, &i);
        mx_new_s_d(line, &mass, j_e_k, &i);
        mx_new_str_d(line, &mass, j_e_k, &i);
        mall_delim(line, &mass, j_e_k, &i);
    }
}

