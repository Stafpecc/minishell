/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:01:18 by tarini            #+#    #+#             */
/*   Updated: 2025/07/03 13:26:50 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <signal.h>
# include "lexer.h"
# include <stdio.h>

extern volatile sig_atomic_t	g_interrupted;

typedef enum e_last_return
{
	CMD_SUCCESS,
	CMD_SYNTAX = 2,
	CMD_NOT_FOUND = 127,
	CMD_INVALID_ARGUMENT,
	CMD_PERMISSION_DENIED = 126,
	CMD_NOT_FOUND_CHILD,
	CMD_EXEC_FAILURE = 255
}	t_last_return;

typedef struct s_redirect_flags
{
	bool	is_heredoc;
	bool	is_append;
}	t_redirect_flags;

typedef struct s_arg
{
	char			*arg;
	int				fd;
	bool			heredoc;
	bool			append_redirect;
	bool			in_simple_quote;
	bool			in_double_quote;
}	t_arg;

typedef struct s_command
{
	t_arg				**cmd_parts;
	t_arg				**redirect_in;
	t_arg				**redirect_out;
	struct s_command	*next;
}	t_command;

typedef struct s_redirect
{
	char	*arg;
	int		fd;
	bool	append_redirect;
	bool	heredoc;
}	t_redirect;

typedef struct s_command_exec
{
	char					**cmd_parts;
	t_redirect				**redirect_in;
	t_redirect				**redirect_out;
	struct s_command_exec	*next;
}	t_command_exec;

typedef struct s_utils
{
	char				**env;
	int					last_return;
	int					num_nodes;
	int					previous_pipes;
	int					status;
	int					old_stdin;
	int					old_stdout;
	int					run;
	size_t				size_env;
	enum e_token_type	type_of_first_arg;
}	t_utils;

typedef struct s_context
{
	t_command	*head;
	t_utils		*utils;
}	t_context;

typedef struct s_redir_params
{
	t_arg				***redirect_array;
	int					i;
	t_redirect_flags	flags;
}	t_redir_params;

typedef enum e_file_mode
{
	FILE_READ,
	FILE_WRITE,
	FILE_EXEC
}	t_file_mode;

/******************************************************************************/
/*                                PARSING                                     */
/******************************************************************************/
t_command_exec	*parse_tokens(t_token *tokens, t_utils *utils);
int				parse_cmd(t_command *cmd, t_utils *utils);
int				launch_commands(t_token **tokens, t_command **curr,
					t_command *head, t_utils *utils);

/******************************************************************************/
/*                                 PARSE                                      */
/******************************************************************************/
bool			is_empty_command(t_command *cmd);
int				return_failure(const char *token, t_utils *utils);
void			print_syntax_error(const char *token, t_utils *utils);
bool			is_directory(const char *path);
int				check_file(const char *path, t_utils *utils, t_file_mode mode);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/
void			free_commands(t_command *cmd);
void			free_commands_exec(t_command_exec *cmd);
t_command		*create_command(void);
t_command_exec	*struct_to_char(t_command *cmd);
void			print_syntax_error(const char *token, t_utils *utils);
int				is_redirect_or_pipe(t_token *token);
int				get_size_of_redirect(t_arg **redirect);
int				is_redirect(t_token *token);
void			free_str_array(char **arr, int size);
t_redirect		**dup_targ_to_tredirect_array(t_arg **arr);
int				cmd_part_to_char(t_command *cmd, t_command_exec *new_node);
void			free_redirect_array(t_redirect **redirects);

/******************************************************************************/
/*                                PROCESS                                     */
/******************************************************************************/
bool			is_word_like(t_token *token);
int				process_word_string(t_token **tokens, t_command *curr,
					t_utils *utils);
int				process_redirect_in(t_token **tokens, t_command *curr,
					t_command *head, t_utils *utils);
int				process_redirect_out(t_token **tokens, t_command *curr,
					t_command *head, t_utils *utils);
int				process_append_redirect(t_token **tokens, t_command *curr,
					t_command *head, t_utils *utils);
void			process_quotes(t_token *tokens, t_arg *arg);
int				process_pipe(t_command **curr, t_command *head);
int				process_heredoc(t_token **tokens, t_command *curr,
					t_command *head, t_utils *utils);
int				process_free_exit(t_command *head);

/******************************************************************************/
/*                              ADD_REDIRECT                                  */
/******************************************************************************/
int				add_redirect(t_token **tokens, t_arg ***redirect_array,
					t_context *ctx, t_redirect_flags flags);

/******************************************************************************/
/*                                 EXPAND                                     */
/******************************************************************************/
char			*expand_variables(char *input, t_utils *utils);
char			*get_env_value(char **env, const char *var_name);
char			*strjoin_and_free(char *s1, char *s2);

#endif
