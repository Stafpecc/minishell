#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h> 

#include "lexer.h"
#include "parsing.h"
#include "exec.h"
#include "signal_handler.h"
#include "../libft/includes/libft.h"

#endif

void print_tokens(t_token *head); // DEBUG
void print_commands(t_command *cmd);
void print_command_exec(t_command_exec *cmd);
