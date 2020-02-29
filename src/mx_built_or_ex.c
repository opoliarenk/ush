#include "../inc/ush.h"


static void builtin(char **mass) {
    char *builts[8] = {"echo", "cd", "pwd", "which", "env", "export", "unset", "exit", "fg"};
    int j = 0;

    for (int i = 0; mass[i]; i++) {
        if (strcmp(mass[i], builts[j]) == 0) {
          //выполнение какой-либо функи  
        }
        j++;
    }
}


void mx_built_or_ex(char **mass) { //функа которая распределяет наши аргументы в терминали билтины или это другие комманды


}
