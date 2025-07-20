/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:57:15 by tarini            #+#    #+#             */
/*   Updated: 2025/07/20 16:14:51 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_operator_token(t_token *token)
{
	return (token->type == TOK_PIPE
		|| token->type == TOK_REDIRECT_IN
		|| token->type == TOK_REDIRECT_OUT
		|| token->type == TOK_APPEND_REDIRECT
		|| token->type == TOK_HEREDOC);
}

static bool	is_valid_word_token(t_token *token)
{
	return (token->type == TOK_WORD
		|| token->type == TOK_STRING
		|| token->type == TOK_SINGLE_QUOTES
		|| token->type == TOK_DOUBLE_QUOTES);
}

static t_token	*check_start_token(t_token *token)
{
	if (is_operator_token(token))
		return (token);
	return (NULL);
}

static t_token	*check_token_pair(t_token *curr)
{
	if (curr->type == TOK_PIPE && curr->next->type == TOK_PIPE)
		return (curr->next);
	if (curr->type == TOK_REDIRECT_IN || curr->type == TOK_REDIRECT_OUT
		|| curr->type == TOK_APPEND_REDIRECT || curr->type == TOK_HEREDOC)
	{
		if (!is_valid_word_token(curr->next))
			return (curr->next);
	}
	return (NULL);
}

t_token	*find_syntax_error(t_token *tokens)
{
	t_token	*curr;
	t_token	*error;

	if (!tokens)
		return (NULL);
	error = check_start_token(tokens);
	if (error)
		return (error);
	curr = tokens;
	while (curr && curr->next)
	{
		error = check_token_pair(curr);
		if (error)
			return (error);
		curr = curr->next;
	}
	return (NULL);
}
