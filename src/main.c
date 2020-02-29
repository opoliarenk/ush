#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    bool exibit = true;
    int i = 0;

    while (exibit) {
        printf("u$h> ");
        line = mx_wait_line(); //mx_canon();
        if (line) {
            mass = mx_connectors(line);
            if (mass[0] != NULL) {
                if (strcmp(mass[0], "-1") == 0)
                    return 0;
                while(mass[i]) {
                    mx_logic(mass[i]);
                    i++;
                }
            }
            for (int i = 0; mass[i]; i++)
                if (mx_ifstrstr(mass[i], "exit"))
                    exibit = false;
        }
        
    }
    return 0;
}
