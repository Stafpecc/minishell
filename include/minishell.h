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
//#include "builtin.h"
#include "signal_handler.h"
#include "../libft/includes/libft.h"

#define RED "\033[0;31m"
#define RESET "\033[0m"

/******************************************************************************/
/*                                DEBUG TO DEL                                */
/******************************************************************************/
void print_commands(t_command *cmd); // DEBUG
void print_tokens(t_token *head); // DEBUG
void print_command_exec(t_command_exec *cmd); // DEBUG
void print_utils_struct(t_utils *utils); // DEBUG
const char *get_token_type_str(t_token_type type); //DEBUG

/******************************************************************************/
/*                                MINISHELL                                   */
/******************************************************************************/
void	minishell_loop(t_utils *utils);
void	execute_or_cleanup(t_command_exec *cmd, t_token *token, char *input, t_utils *utils);
t_token	*process_lexer(char *input, t_utils *utils);
t_utils *init_utils_struct(char **envp);

/******************************************************************************/
/*                                SECURE                                      */
/******************************************************************************/
int check_error(int ac);
void free_env(char **env);
void free_utils(t_utils *utils);
void	exit_proprely(int count, ...);

/******************************************************************************/
/*                                QUOTES                                      */
/******************************************************************************/
char *read_input_with_quotes(void);
char	quote_not_closed(const char *str);


#endif

