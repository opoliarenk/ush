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
            if (mass[0]) {
                while(mass[i]) {
                    mx_logic(mass[i]);
                    i++;
                }
                i = 0;
            }
            for (int j = 0; mass[j]; j++)
                if (strcmp(mass[j], "exit") == 0)
                    exibit = false;
        }
        
    }
    return 0;
}
