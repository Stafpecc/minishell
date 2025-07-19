/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:57:15 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 22:51:49 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_syntax_error(t_token *tokens)
{
	t_token	*curr;

	if (!tokens)
		return (NULL);
	if (tokens->type == TOK_PIPE
		|| tokens->type == TOK_REDIRECT_IN
		|| tokens->type == TOK_REDIRECT_OUT
		|| tokens->type == TOK_APPEND_REDIRECT
		|| tokens->type == TOK_HEREDOC)
		return (tokens);
	curr = tokens;
	while (curr && curr->next)
	{
		if (curr->type == TOK_PIPE && curr->next->type == TOK_PIPE)
			return (curr->next);
		if ((curr->type == TOK_REDIRECT_IN || curr->type == TOK_REDIRECT_OUT
				|| curr->type == TOK_APPEND_REDIRECT || curr->type
				== TOK_HEREDOC))
		{
			if (curr->next->type != TOK_WORD && curr->next->type != TOK_STRING
				&& curr->next->type != TOK_SINGLE_QUOTES && curr->next->type
				!= TOK_DOUBLE_QUOTES)
				return (curr->next);
		}
		curr = curr->next;
	}
	return (NULL);
}
