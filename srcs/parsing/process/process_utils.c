/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:58:07 by tarini            #+#    #+#             */
/*   Updated: 2025/07/15 13:45:23 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "parsing.h"
#include "../../../libft/includes/libft.h"

/*
Function that:
- checks if a token is considered a valid word or string during parsing;
- returns true if the token type is a simple word or a quoted string,
false otherwise.
*/
bool	is_word_like(t_token *token)
{
	return (token->type == TOK_WORD
		|| token->type == TOK_STRING
		|| token->type == TOK_SINGLE_QUOTES
		|| token->type == TOK_DOUBLE_QUOTES);
}

/*
Function that:
- checks if a token corresponds to a redirection (<<, >>, <, >)
  or a pipe (|);
- returns RETURN_SUCCESS if it does, otherwise RETURN_FAILURE.
*/
int	is_redirect_or_pipe(t_token *token)
{
	if (!token)
		return (RETURN_FAILURE);
	if (ft_strcmp(token->value, "<<") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, ">>") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, "<") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, ">") == 0)
		return (RETURN_SUCCESS);
	if (ft_strcmp(token->value, "|") == 0)
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

int	is_redirect(t_token *token)
{
	return (token->type == TOK_REDIRECT_OUT
		|| token->type == TOK_REDIRECT_IN
		|| token->type == TOK_HEREDOC
		|| token->type == TOK_APPEND_REDIRECT);
}
