/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:27:57 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 21:01:25 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdbool.h>

# include "return_error.h"

typedef struct s_utils	t_utils;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_REDIRECT_OUT,
	TOK_REDIRECT_IN,
	TOK_STRING,
	TOK_HEREDOC,
	TOK_SINGLE_QUOTES,
	TOK_DOUBLE_QUOTES,
	TOK_APPEND_REDIRECT,
	TOK_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_token_ctx
{
	const char	*input;
	size_t		*i;
	t_token		**head;
	char		**buffer;
}	t_token_ctx;

/******************************************************************************/
/*                                 LEXER                                      */
/******************************************************************************/
int			launch_tokens(const char *input, size_t *i, t_token **head,
				t_utils *utils);
t_token		*lexer(const char *input, t_utils *utils);

/******************************************************************************/
/*                                 UTILS                                      */
/******************************************************************************/
char		*ft_strndup(const char *s, size_t n);
int			ft_isspace(char c);
void		free_tokens(t_token *head);
int			has_only_one_redirection(t_token *head);
t_token		*create_token(t_token_type type, const char *value);
int			add_token(t_token **head, t_token_type type, const char *value);

/******************************************************************************/
/*                                PROCESS                                     */
/******************************************************************************/
int			process_combined_token(const char *input, size_t *i,
				t_token **head, t_utils *utils);
int			process_quoted_token_separate(const char *input, size_t *i,
				t_token **head, char quote);
int			handle_quoted_token(t_token_ctx *ctx, char quote, t_utils *utils);
char		*extract_quoted_part(const char *input, size_t *i, char quote);
char		*concat_buffer_part(char *buffer, char *part);
int			handle_double_quotes_with_expansion(t_token_ctx *ctx,
				t_utils *utils);
int			handle_single_quotes(t_token_ctx *ctx);
bool		is_separator(char c);
bool		is_separate_quoted(const char *input, size_t i, char quote,
				char *buffer);
int			append_quoted_to_buffer(const char *input, size_t *i,
				char quote, char **buffer);

#endif