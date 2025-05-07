#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"

typedef struct s_command {
	char **cmd;
	char *redirect_in;
	char *redirect_out;
	char *append_redirections;
	char *heredoc;
	struct s_command *next;
} t_command;

void free_commands(t_command *cmd);
t_command *parse_tokens(t_token *tokens);

char **add_argument(char **args, const char *value);
t_command *create_command();

int process_parsing(t_token *tokens, t_command *curr, t_command *head);

#endif
