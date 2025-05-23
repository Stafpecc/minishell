#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"

typedef struct s_arg {
	char			*arg;
	bool			in_simple_quote;
	bool			in_double_quote;
} t_arg;

typedef struct s_command {
	t_arg			**cmd_parts;
	t_arg			*redirect_in;
	t_arg			*redirect_out;
	t_arg			*append_redirections;
	t_arg			*heredoc;
	struct s_command *next;
} t_command;

typedef struct s_command_exec {
	char			**cmd_parts;
	char			*redirect_in;
	char			*redirect_out;
	char			*append_redirections;
	char			*heredoc;
	struct 			s_command_exec *next;
} t_command_exec;

typedef struct s_utils {
	char			**env;
	int         	last_return;
	int         	num_nodes;
	int         	previous_pipes;
	int 			status;
} t_utils;

/******************************************************************************/
/*                                PARSING                                     */
/******************************************************************************/
t_command_exec	*parse_tokens(t_token *tokens);
int				parse_cmd(t_command *cmd);
int				launch_commands(t_token **tokens, t_command **curr, t_command *head);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/
void			free_commands(t_command *cmd);
void 			free_commands_exec(t_command_exec *cmd);
t_command		*create_command();
t_arg			**add_argument(t_arg **args, const char *value);
t_command_exec	*struct_to_char(t_command *cmd);
void			print_syntax_error(const char *token);

/******************************************************************************/
/*                                PROCESS                                     */
/******************************************************************************/
bool			is_word_like(t_token *token);
int				process_word_string(t_token **tokens, t_command *curr);
int				process_redirect_in(t_token **tokens, t_command *curr, t_command *head);
int				process_redirect_out(t_token **tokens, t_command *curr, t_command *head);
int				process_append_redirect(t_token **tokens, t_command *curr, t_command *head);
void			process_quotes(t_token *tokens, t_arg *arg);
int				process_pipe(t_command **curr, t_command *head);
int				process_heredoc(t_token **tokens, t_command *curr, t_command *head);
int				process_free_exit(t_command *head);

#endif
