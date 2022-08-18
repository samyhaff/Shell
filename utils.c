#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "utils.h"

// char *read_line() {
//     int buffsize = BUFFSIZE;
//     int position = 0;
//     char *buffer = malloc(sizeof(char) * buffsize);
//     int c;
//
//     if (!buffer) {
//         fprintf(stderr, "allocation error\n");
//         exit(EXIT_FAILURE);
//     }
//
//     while (1) {
//         c = getchar();
//
//         if (c == EOF || c == '\n') {
//             buffer[position] = '\0';
//             return buffer;
//         } else {
//             buffer[position] = c;
//         }
//         position++;
//
//         if (position >= buffsize) {
//             buffsize += BUFFSIZE;
//             buffer = realloc(buffer, sizeof(char) * buffsize);
//             if (!buffer) {
//                 fprintf(stderr, "allocation error\n");
//                 exit(EXIT_FAILURE);
//             }
//         }
//     }
// }

char *read_line()
{
    char *line = NULL;
    ssize_t buffsize = 0;

    if (getline(&line, &buffsize, stdin) == -1){
        if (feof(stdin)) exit(EXIT_SUCCESS);
        else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
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

int launch(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("sch");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) perror("sch");
    else {
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }

    return 1;
}

char *builtin_str[] = {
    "cd",
    "help",
    "quit"
};

int (*builtin_func[]) (char **) = {
    &cd,
    &help,
    &quit
};

int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

int cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) perror("sch");
    }
    return 1;
}

int help(char **args)
{
    int i;
    printf("The following are built in:\n");
    for (i = 0; i < num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }
    return 1;
}

int quit(char **args)
{
    return 0;
}

int execute(char **args) {
    int i;

    if (args[0] == NULL) return 1;

    for (i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)  return (*builtin_func[i])(args);
    }

    return launch(args);
}
