#ifndef UTILS
#define UTILS

#define BUFFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

int cd(char **args);
int help(char **args);
int quit(char **args);
char *read_line();
char **split_line(char *);
int execute(char **);

#endif
