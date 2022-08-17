#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void loop() {
    char *line, **args;
    int status;

    do {
        printf("sch> ");
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
