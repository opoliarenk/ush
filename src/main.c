#include "../inc/ush.h"

int main() {
    char *line;
    char **mass;
    int i = 0;

    while (1) {
        printf("u$h> ");
        line = mx_canon();
        mass = mx_connectors(line);
        if (mass) {
            if (strcmp(mass[0], "-1") == 0)
                return 0;
            while(mass[i]) {
                mx_logic(mass[i])
            }
        }
        
    }
    return 0;
}
