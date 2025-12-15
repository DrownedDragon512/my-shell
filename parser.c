#include "parser.h"
#include <string.h>

int split_pipeline(char *line, char **cmds) {
    int count = 0;
    char *token = strtok(line, "|");
    while (token && count < MAX_CMDS) {
        cmds[count++] = token;
        token = strtok(NULL, "|");
    }
    return count;
}

void parse_args(char *cmd, char **args,
                char **in, char **out,
                int *append, int *bg) {

    int i = 0;
    *in = *out = NULL;
    *append = *bg = 0;

    char *token = strtok(cmd, " \n");
    while (token && i < MAX_ARGS - 1) {
        if (!strcmp(token, "<"))
            *in = strtok(NULL, " \n");
        else if (!strcmp(token, ">")) {
            *out = strtok(NULL, " \n");
            *append = 0;
        }
        else if (!strcmp(token, ">>")) {
            *out = strtok(NULL, " \n");
            *append = 1;
        }
        else if (!strcmp(token, "&"))
            *bg = 1;
        else
            args[i++] = token;

        token = strtok(NULL, " \n");
    }
    args[i] = NULL;
}
