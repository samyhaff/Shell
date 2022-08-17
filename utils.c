#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *read_line() {
    int buffsize = BUFFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * buffsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= buffsize) {
            buffsize += BUFFSIZE;
            buffer = realloc(buffer, sizeof(char) * buffsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **split_line(char *line) {
    int buffsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(buffsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= buffsize) {
            buffsize += TOK_BUFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
