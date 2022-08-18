#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void loop() {
    char *line, **args;
    int status;

    do {
        printf("\033[1;31msch>\033[0m ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char *argv[]) {
    loop();
    return EXIT_SUCCESS;
}
