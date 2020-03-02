#include "../inc/ush.h"
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **ush_split_line(char *line) {
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        //fprintf(stderr, "lsh: ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

    if (position >= bufsize) {
        bufsize += LSH_TOK_BUFSIZE;
        tokens = realloc(tokens, bufsize * sizeof(char*));
        if (!tokens) {
            //fprintf(stderr, "lsh: ошибка выделения памяти\n");
            exit(EXIT_FAILURE);
        }
    }
    token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

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
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        close(1);
        fd = open(str, O_WRONLY);
        if (fd == -1) {
            fd = open(str, O_CREAT | O_WRONLY);
        }
        dup2(fd, 1);
        //
        mx_printstr(mass[0]);
        mx_printchar('\n');
        exit(0);
        //выполнять функу назара
    }
    waitpid(pid, &status, 0);
}

static void creat_file_add(char *str, char **mass) {
    int fd;
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        close(1);
        fd = open(str, O_APPEND | O_WRONLY);
        if (fd == -1) {
            fd = open(str, O_CREAT | O_APPEND | O_WRONLY);
        }
        dup2(fd, 1);
        ///////
        mx_printstr(mass[0]);
        mx_printchar('\n');
        exit(0);
        ///////выполнять функу назара
    }
    waitpid(pid, &status, 0);
}

int mx_redir(char *line) {
    char *newl = easy_split(line);
    char **mass = ush_split_line(newl);
    int n = 0;
    while (mass[n]) {
        mx_printstr(mass[n]);
        n++;
    }
    
    for (int i = 0; mass[i] != NULL; i++) {
        if (strcmp(mass[i], ">") == 0 && strcmp(mass[i + 1], ">") == 0) {
            i = i + 1;
            creat_file_add(mass[i + 1], mass);
            continue;
        }
        if (strcmp(mass[i], ">") == 0) {
            creat_file_one(mass[i + 1], mass);
        }
    }
    return 0;
}
