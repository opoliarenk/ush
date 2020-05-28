#include "../inc/ush.h"

static int spec_symbol(char *line, int *i, int *j_k_c_ko, char ***mass);

static void special_eq(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == '\\' && line[(*i) + 1] == ' ') {
        (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i) + 1];
        j_k_c_ko[1]++;
        (*i) = (*i) + 2;
        if (line[(*i)] == '\\')
            spec_symbol(line, i, j_k_c_ko, mass);
    }
}

static int spec_symbol(char *line, int *i, int *j_k_c_ko, char ***mass) {
    int is = 0;

    if (line[(*i)] == '\\' && line[(*i) + 1] == '\\'
        && mx_check_for_echoE(line) != true) {
        while (line[(*i)] == '\\') {
            (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
            j_k_c_ko[1]++;
            (*i)++;
            while (j_k_c_ko[2] != 3 && line[(*i)] == '\\') {
                j_k_c_ko[2]++;
                (*i)++;
                is = 1;
            }
            j_k_c_ko[2] = 0;
            if (is == 1)
                break; 
        }
    } 
    special_eq(line, i, j_k_c_ko, mass);
    if (line[(*i)] == '\\') {
        (*i)++;
        return 0;
    }
    return 1;
}

static void main_delim(char *line, int *i, int *j_k_c_ko, char ***mass) {
    if (line[(*i)] == ' ' || line[(*i)] == '\t' 
        || line[(*i)] == '\r' || line[(*i)] == '\n' 
        || line[(*i)] == '\a' || line[(*i) + 1] == '\0') {
        while (line[(*i) + 1] == ' ' || line[(*i) + 1] == '\t' 
            || line[(*i) + 1] == '\r' || line[(*i) + 1] == '\n' 
            || line[(*i) + 1] == '\a')
            (*i)++;
        if (line[(*i) + 1] == '\0' && line[(*i)] != ' ' && line[(*i)] != '\t' 
            && line[(*i)] != '\r' && line[(*i)] != '\n' 
            && line[(*i)] != '\a') {
            (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
        }
        j_k_c_ko[0]++;
        j_k_c_ko[1] = 0;
    }
    else {
        (*mass)[j_k_c_ko[0]][j_k_c_ko[1]] = line[(*i)];
        j_k_c_ko[1]++;
        if (line[(*i)] == '\0') 
            j_k_c_ko[0]++;
    } 
}

static int funcs(char *line, int *i, int *j_k_c_ko, char ***mass) {
    int p = spec_symbol(line, i, j_k_c_ko, mass);
    if (p == 1) {
        mx_sky_doubt(line, i, j_k_c_ko, mass);
        mx_sub_pars(line, i, j_k_c_ko, mass);
        mx_sub_doll_p(line, i, j_k_c_ko, mass);
    }
    return p;
}

char **mx_delim_space(char *line) { 
    char **mass = malloc(sizeof(char*) * mx_countingw(line) + 1);
    int j_k_c_ko[4] = {0, 0, 0, 0};
    int len = strlen(line);
    int p;

    mx_new_malloc(mass, line);
    for (int i = 0; i < len; i++) {
        p = funcs(line, &i, j_k_c_ko, &mass);
        if (p == 1 && line[i] == '\"') {
            mx_doubl_d(line, &i, j_k_c_ko, &mass);
            if (line[i] == '\0') {
                j_k_c_ko[0]++;
                break;
            }
        }
        main_delim(line, &i, j_k_c_ko, &mass);
    }
    mass[j_k_c_ko[0]] = NULL;
    return mass;
}

