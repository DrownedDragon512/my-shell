#define _POSIX_C_SOURCE 200809L
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jobs.h"
#include "parser.h"
#include "exec.h"
#include "script.h"
#include "ui.h"

int main(int argc, char *argv[]) {

    if (argc == 2) {
        FILE *fp = fopen(argv[1], "r");
        if (!fp) {
            perror("script");
            return 1;
        }
        run_script(fp);
        fclose(fp);
        return 0;
    }

    print_startup_banner();

    char *line = NULL;
    size_t size = 0;

    while (1) {
        reap_background_processes();
        print_prompt();

        if (getline(&line, &size, stdin) == -1)
            break;

        char line_copy[256];
        strncpy(line_copy, line, 255);
        line_copy[255] = '\0';

        char *cmds[MAX_CMDS];
        int n_cmds = split_pipeline(line, cmds);

        char *args[MAX_ARGS], *in, *out;
        int append, bg;
        parse_args(cmds[0], args, &in, &out, &append, &bg);

        if (!args[0])
            continue;

        if (!strcmp(args[0], "exit"))
            break;

        if (!strcmp(args[0], "cd")) {
            if (args[1])
                chdir(args[1]);
            continue;
        }

        if (!strcmp(args[0], "jobs")) {
            list_jobs();
            continue;
        }

        if (!strcmp(args[0], "fg")) {
            Job *job = find_job(atoi(args[1]));
            if (job) {
                waitpid(job->pid, NULL, 0);
                job->running = 0;
            }
            continue;
        }

        if (!strcmp(args[0], "goat")) {
            print_goat();
            continue;
        }

        if (!strcmp(args[0], "description")) {
            print_description();
            continue;
        }

        if (n_cmds == 1) {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                exit(1);
            }
            if (!bg)
                waitpid(pid, NULL, 0);
            else
                add_job(pid, line_copy);
        } else {
            execute_pipeline(cmds, n_cmds, bg);
        }
    }

    free(line);
    return 0;
}
