#ifndef PARSING_H
# define PARSING_H

# include "lexer.h"

typedef enum e_last_return {
    CMD_SUCCESS,
    CMD_NOT_FOUND,
    CMD_INVALID_ARGUMENT,
    CMD_PERMISSION_DENIED = 126,
    CMD_NOT_FOUND_CHILD,
    CMD_EXEC_FAILURE = 255
} t_last_return;

typedef struct s_heredoc {
	char	*arg;
	int		fd;
} t_heredoc;

typedef struct s_arg {
	char			*arg;
	int				fd;
	bool			in_simple_quote;
	bool			in_double_quote;
} t_arg;

typedef struct s_command {
	t_arg			**cmd_parts;
	t_arg			**redirect_in;
	t_arg			**redirect_out;
	t_arg			*append_redirections;
	t_arg			*heredoc;
	struct s_command *next;
} t_command;

typedef struct s_command_exec {
	
	char			**cmd_parts;
	char			**redirect_in;
	char			**redirect_out;
	char			*append_redirections;
	t_heredoc		*heredoc;
	struct 			s_command_exec *next;
} t_command_exec;

typedef struct s_utils {
	char				**env;
	int         		last_return;
	int         		num_nodes;
	int         		previous_pipes;
	int 				status;
	enum e_token_type	type_of_first_arg;
} t_utils;

typedef enum e_file_mode {
	FILE_READ,
	FILE_WRITE,
	FILE_EXEC
}	t_file_mode;

/******************************************************************************/
/*                                PARSING                                     */
/******************************************************************************/
t_command_exec	*parse_tokens(t_token *tokens, t_utils *utils);
int				parse_cmd(t_command *cmd, t_utils *utils);
int				launch_commands(t_token **tokens, t_command **curr, t_command *head, t_utils *utils);

/******************************************************************************/
/*                                 PARSE                                      */
/******************************************************************************/
bool			is_empty_command(t_command *cmd);
int				return_failure(const char *token, t_utils *utils);
void 			print_syntax_error(const char *token, t_utils *utils);
int 			redirect_parsing(t_command *curr, t_utils *utils);
bool 			has_conflicting_redirections(t_command *cmd);
bool 			is_directory(const char *path);
int 			check_file(const char *path, t_utils *utils, t_file_mode mode);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/
void			free_commands(t_command *cmd);
void 			free_commands_exec(t_command_exec *cmd);
t_command		*create_command();
t_arg			**add_argument(t_arg **args, const char *value);
t_command_exec	*struct_to_char(t_command *cmd);
void			print_syntax_error(const char *token, t_utils *utils);
int 			is_redirect_or_pipe(t_token *token);
int				get_size_of_redirect(t_arg **redirect);
int				is_redirect(t_token *token);
void			free_str_array(char **arr, int size);
char			**dup_targ_array(t_arg **arr);
t_heredoc		*dup_heredoc_from_arg(t_arg *src);


/******************************************************************************/
/*                                PROCESS                                     */
/******************************************************************************/
bool			is_word_like(t_token *token);
int				process_word_string(t_token **tokens, t_command *curr);
int				process_redirect_in(t_token **tokens, t_command *curr, t_command *head, t_utils  *utils);
int				process_redirect_out(t_token **tokens, t_command *curr, t_command *head, t_utils *utils);
int				process_append_redirect(t_token **tokens, t_command *curr, t_command *head, t_utils *utils);
void			process_quotes(t_token *tokens, t_arg *arg);
int				process_pipe(t_command **curr, t_command *head);
int				process_heredoc(t_token **tokens, t_command *curr, t_command *head, t_utils *utils);
int				process_free_exit(t_command *head);

#endif
