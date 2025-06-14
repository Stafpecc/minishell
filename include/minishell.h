#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h> 

#include "lexer.h"
#include "parsing.h"
#include "exec.h"
#include "env.h"
#include "signal_handler.h"
#include "../libft/includes/libft.h"

void print_commands(t_command *cmd); // DEBUG
void print_tokens(t_token *head); // DEBUG
void print_command_exec(t_command_exec *cmd); // DEBUG
void print_utils_struct(t_utils *utils); // DEBUG
const char *get_token_type_str(t_token_type type); //DEBUG

#endif

