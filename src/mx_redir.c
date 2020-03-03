#include "../inc/ush.h"

static char *easy_split(char *line) {
    int i;
    int j = 0;
    char *new = NULL;
    int k = 0;
    
    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] == '>') 
            j = j + 2;
    }
    i = i + j;
    new = mx_strnew(i);
    for (int q = 0; q < i; q++) {
        if (line[k] == '>') {
            new[q++] = ' ';
            new[q++] = line[k];
            new[q] = ' ';
            k++;
        } 
        else {
            new[q] = line[k];
            k++;
        }
    }
    return new;
}

static void creat_file_one(char *str, char **mass) {
    int fd;
    int save_fd = dup(1);

    close(1);
    fd = open(str, O_WRONLY | O_TRUNC);
    if (fd == -1) {
        fd = open(str, O_CREAT | O_WRONLY);
    }
    dup2(fd, 1);
    ///////
    mx_printstr(mass[0]);
    mx_printstr(mass[1]);
    mx_printstr(mass[2]);
    mx_printchar('\n');
    ///////выполнять функу назара вместо этого мусора!!!Передаю туда mass
    dup2(save_fd, 1);
} 

static void creat_file_add(char *str, char **mass) {
    int fd;
    int save_fd = dup(1);

    close(1);
    fd = open(str, O_APPEND | O_WRONLY);
    if (fd == -1) {
        fd = open(str, O_CREAT | O_APPEND | O_WRONLY);
    }
    dup2(fd, 1);
    ///////
    mx_printstr(mass[0]);
    mx_printstr(mass[1]);
    mx_printstr(mass[2]);
    mx_printchar('\n');
    ///////выполнять функу назара вместо этого мусора!!!!Передаю туда mass
    dup2(save_fd, 1);
}

int mx_redir(char *line) {
    char *newl = easy_split(line); //FREE
    char **mass = mx_sh_splite(newl); //FREE
    char **newmass = NULL;

    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0 && strcmp(mass[i + 1], ">") == 0) {
            i = i + 1;
            newmass = mx_newfor_bults(mass);
            creat_file_add(mass[i + 1], newmass);
            //break;
            continue;
        }
        if (strcmp(mass[i], ">") == 0) {
            newmass = mx_newfor_bults(mass);
            creat_file_one(mass[i + 1], newmass);
            //break;
        }
    }
    return 0;
}
