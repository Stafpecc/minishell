/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:10:48 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 16:19:14 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_word_token(t_token **tokens, t_command *curr, t_utils *utils)
{
	if ((*tokens)->type == TOK_WORD
		|| (*tokens)->type == TOK_DOUBLE_QUOTES
		|| (*tokens)->type == TOK_SINGLE_QUOTES)
	{
		if (process_word_string(tokens, curr, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int	process_redirect_tokens(t_token **tokens, t_command *curr,
	t_command *head, t_utils *utils)
{
	if ((*tokens)->type == TOK_REDIRECT_IN)
	{
		if (process_redirect_in(tokens, curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		return (RETURN_SUCCESS);
	}
	else if ((*tokens)->type == TOK_REDIRECT_OUT)
	{
		if (process_redirect_out(tokens, curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		return (RETURN_SUCCESS);
	}
	else if ((*tokens)->type == TOK_APPEND_REDIRECT)
	{
		if (process_append_redirect(tokens, curr, head, utils)
			== RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int	process_special_tokens(t_token **tokens, t_command **curr,
	t_command *head, t_utils *utils)
{
	if ((*tokens)->type == TOK_HEREDOC)
	{
		if (process_heredoc(tokens, *curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		if (g_interrupted)
		{
			g_interrupted = 0;
			return (RETURN_FAILURE);
		}
	}
	else if ((*tokens)->type == TOK_PIPE)
	{
		if (process_pipe(curr) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int	launch_commands(t_token **tokens, t_command **curr,
	t_command *head, t_utils *utils)
{
	if (process_word_token(tokens, *curr, utils) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (process_redirect_tokens(tokens, *curr, head, utils) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (process_special_tokens(tokens, curr, head, utils) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (*tokens)
		*tokens = (*tokens)->next;
	return (RETURN_SUCCESS);
}
