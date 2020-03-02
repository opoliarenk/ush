#include "../inc/ush.h"

static int redirect(char *line) {
    int posi = 0;

    for (int i = 0; line[i + 1] != '\0'; i++) {
        if (line[i] == '>') {
            mx_redir(line);
            posi++;
            if (line[i + 1] == '>')
                i++;
        } 
    }
    return posi;
}

// static int pipes(char *line) {
//     int posi = 0;

//     for (int i = 0; line[i + 1] != '\0'; i++) {
//         if (line[i] == '|') {
//             // пайпы
//             posi++;
//         }
//     }
//     return posi;
// }

int mx_red_pipe(char *line) { //  проверяет пайпы или редирекшены 
    int redir = redirect(line);
    //int pips = pipes(line);

    if (redir == 0) //pips == 0 ||
        return 1;
    return 0;
}
