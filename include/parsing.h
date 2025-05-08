#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"

typedef struct s_arg {
	char *arg;
	bool in_simple_quote;
	bool in_double_quote;
} t_arg;

typedef struct s_cmd_part {
    char *content;
    bool in_simple_quote;
    bool in_double_quote;
} t_cmd_part;

typedef struct s_command {
	t_cmd_part	**cmd_parts;
	char		*redirect_in;
	char		*redirect_out;
	t_arg		*append_redirections;
	t_arg		*heredoc;
	struct s_command *next;
} t_command;


/******************************************************************************/
/*                                PARSING                                     */
/******************************************************************************/
t_command *parse_tokens(t_token *tokens);
int launch_commands(t_token **tokens, t_command **curr, t_command *head);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/
void free_commands(t_command *cmd);
t_command *create_command();
char **add_argument(char **args, const char *value);

/******************************************************************************/
/*                                PROCESS                                     */
/******************************************************************************/
int process_word_string(t_token **tokens, t_command *curr);
int is_word_like(t_token *token);
int process_redirect_in(t_token **tokens, t_command *curr, t_command *head);
int process_redirect_out(t_token **tokens, t_command *curr, t_command *head);
int process_append_redirect(t_token **tokens, t_command *curr, t_command *head);
void process_quotes_arg(t_token *tokens, t_arg *arg);
void process_quotes_cmd(t_token *token, t_cmd_part *cmd_part);
int process_pipe(t_command **curr, t_command *head);
int process_heredoc(t_token **tokens, t_command *curr, t_command *head);

#endif
