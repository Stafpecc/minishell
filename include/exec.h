#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
//exec.c
void exec(char *input, char **env);

//simple_cmd.c

void init_simple_cmd (char *input, char **env);

#endif