#include "../inc/ush.h"

static int redirectin(char *line) {
    int posi = 0;

    for (int i = 0; line[i + 1] != '\0'; i++) {
        if (line[i] == '>') {
            mx_redir(line); // работает но назара функи надо
            posi++;
            if (line[i + 1] == '>')
                i++;
        } 
    }
    return posi;
}

// static int redirectout(char *line) {
//     int posi = 0;

//     for (int i = 0; line[i + 1] != '\0'; i++) {
//         if (line[i] == '<') {
//             mx_redirout(line); // изменить 
//             posi++;
//             if (line[i + 1] == '<')
//                 i++;
//         } 
//     }
//     return posi;
// }

int mx_red_pipe(char *line) { //  проверяет или есть редирекшены , сначала или их не два одновременно, а потом каждый по отдельности 
    redirectin(line); //один редирект ввод int redirin = 
    // int redirout = redirectout(line); //один редирект вывод 
    // int lenline = strlen(line);
    // int in = 0;
    // int out = 0;

    // for (int i = 0; i < lenline; i++) {
    //     if (line[i] == '<')
    //         in = 1;
    //     else if (line[i] == '>') 
    //         out = 1; 
    // }
    // if (in == 1 && out == 1) {
        
    // }
    return 0;
}
