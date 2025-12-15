#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 100
#define MAX_CMDS 20

int split_pipeline(char *line, char **cmds);
void parse_args(char *cmd, char **args,
                char **in, char **out,
                int *append, int *bg);

#endif
