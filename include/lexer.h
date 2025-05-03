#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdbool.h>
//sigil + digit?)
typedef enum e_token_type {
	TOK_WORD,
    TOK_PIPE,
    TOK_REDIRECT_OUT,
    TOK_REDIRECT_IN,
    TOK_STRING,
    TOK_END
} t_token_type;

typedef struct s_token {
	bool return_value;
    t_token_type type;
    char *value;
    struct s_token *next;
} t_token;

char	*ft_strndup(const char *s, size_t n);
int		ft_isspace(char c);

void 	free_tokens(t_token *head);
t_token	*lexer(const char *input);

int has_word_token(t_token *head);

#endif