/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:28:38 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 15:09:44 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h> 

# include "lexer.h"
# include "parsing.h"
# include "exec.h"
# include "env.h"
# include "signal_handler.h"
# include "../libft/includes/libft.h"

# define RED "\033[0;31m"
# define RESET "\033[0m"

/******************************************************************************/
/*                                MINISHELL                                   */
/******************************************************************************/
void		minishell_loop(t_utils *utils);
void		execute_or_cleanup(t_command_exec *cmd, t_token *token, char *input,
				t_utils *utils);
t_token		*process_lexer(char *input, t_utils *utils);
t_utils		*init_utils_struct(char **envp);
bool		skip_empty_or_spaces(char *input);
bool		handle_null_input(char *input, t_utils *utils);

/******************************************************************************/
/*                                SECURE                                      */
/******************************************************************************/
int			check_error(int ac);
void		free_env(char **env);
void		free_utils(t_utils *utils);
void		exit_proprely(int count, ...);

/******************************************************************************/
/*                                QUOTES                                      */
/******************************************************************************/
char		*read_input_with_quotes(t_utils *utils);
char		quote_not_closed(const char *str);

#endif