#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
#include "minishell.h"
#include "lexer.h"
#include "parsing.h"
#include "signal_handler.h"
#include "../libft/includes/libft.h"


//exec.c
void	exec(t_command *node);

#endif