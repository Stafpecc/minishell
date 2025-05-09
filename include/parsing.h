#ifndef PARSING_H
# define PARSING_H

#include "lexer.h"

typedef struct s_command {
	char **cmd;
	char *redirect_in;
	char *redirect_out;
	struct s_command *next;
} t_command;

void free_commands(t_command *cmd);
t_command *parse_tokens(t_token *tokens);

#endif
