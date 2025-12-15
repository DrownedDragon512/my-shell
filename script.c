#define _POSIX_C_SOURCE 200809L
#include "script.h"
#include "parser.h"
#include "exec.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void run_script(FILE *fp) {
    char *line = NULL;
    size_t size = 0;

    while (getline(&line, &size, fp) != -1) {
        if (line[0] == '\n' || line[0] == '#')
            continue;

        char *cmds[MAX_CMDS];
        int n_cmds = split_pipeline(line, cmds);

        if (n_cmds == 1) {
            if (fork() == 0) {
                execvp(cmds[0], (char *[]){cmds[0], NULL});
                _exit(1);
            }
            wait(NULL);
        } else {
            execute_pipeline(cmds, n_cmds, 0);
        }
    }
    free(line);
}
