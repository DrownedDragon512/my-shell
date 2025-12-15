#include "exec.h"
#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void execute_pipeline(char **cmds, int n, int bg) {
    int pipes[2 * (n - 1)];

    for (int i = 0; i < n - 1; i++)
        pipe(pipes + i * 2);

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            if (i > 0)
                dup2(pipes[(i - 1) * 2], STDIN_FILENO);
            if (i < n - 1)
                dup2(pipes[i * 2 + 1], STDOUT_FILENO);

            for (int j = 0; j < 2 * (n - 1); j++)
                close(pipes[j]);

            char *args[MAX_ARGS], *in, *out;
            int append, bg2;
            parse_args(cmds[i], args, &in, &out, &append, &bg2);

            if (in) {
                int fd = open(in, O_RDONLY);
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            if (out) {
                int fd = open(out,
                    append ? O_WRONLY | O_CREAT | O_APPEND
                           : O_WRONLY | O_CREAT | O_TRUNC,
                    0644);
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }

            execvp(args[0], args);
            perror("exec");
            exit(1);
        }
    }

    for (int i = 0; i < 2 * (n - 1); i++)
        close(pipes[i]);

    if (!bg)
        for (int i = 0; i < n; i++)
            wait(NULL);
}
