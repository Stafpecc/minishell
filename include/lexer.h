/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:27:57 by tarini            #+#    #+#             */
/*   Updated: 2025/07/14 15:33:30 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdbool.h>

# include "return_error.h"

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
int			launch_tokens(const char *input, size_t *i, t_token **head);
t_token		*lexer(const char *input);

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
				t_token **head);
int			process_quoted_token_separate(const char *input, size_t *i,
				t_token **head, char quote);
int			handle_quoted_token(t_token_ctx *ctx, char quote);
char		*extract_quoted_part(const char *input, size_t *i, char quote);
char		*concat_buffer_part(char *buffer, char *part);

#endif