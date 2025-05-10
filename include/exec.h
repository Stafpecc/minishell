#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include "minishell.h"
#include "lexer.h"
#include "parsing.h"
#include "signal_handler.h"
#include "../libft/includes/libft.h"

//child_dup.c
int		outfile_dup(char *redirect, int *pipe_fd, int fd);
int		infile_dup(char *redirect, int *pipe_fd, int previous_pipe, int fd);
void	child_init_pipes_dup(t_command *node, int *pipe_fd, int previous_pipe);

//exec.c
void	exec(t_command *node);

#endif