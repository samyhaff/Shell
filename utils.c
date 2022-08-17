#include <stdio.h>
#include <stdlib.h>
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

        if (position == buffsize) {
            buffsize += BUFFSIZE;
            buffer = realloc(buffer, sizeof(char) * buffsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
