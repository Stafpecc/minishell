/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:28:38 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 16:13:45 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h> 

# include "parsing.h"
# include "exec.h"
# include "env.h"
# include "signal_handler.h"
# include "../libft/includes/libft.h"

# define RED "\033[0;31m"
# define RESET "\033[0m"
# define MAG "\e[0;35m"
# define YEL "\e[0;33m"
# define CYN "\e[0;36m"

/******************************************************************************/
/*                                MINISHELL                                   */
/******************************************************************************/
void		minishell_loop(t_utils *utils);
void		execute_or_cleanup(t_command_exec *cmd, t_token *token, char *input,
				t_utils *utils);
t_token		*process_lexer(char *input, t_utils *utils);
t_utils		*init_utils_struct(char **envp);

/******************************************************************************/
/*                                SECURE                                      */
/******************************************************************************/
int			check_error(int ac);
void		free_env(char **env);
void		free_utils(t_utils *utils);

/******************************************************************************/
/*                                QUOTES                                      */
/******************************************************************************/
char		*read_input_with_quotes(t_utils *utils);
char		quote_not_closed(const char *str);

/******************************************************************************/
/*                                ASCII                                       */
/******************************************************************************/

void		ascii_minishell(char *line);
void		ascii_tarini(char *line);
void		ascii_ldevoude(char *line);

#endif