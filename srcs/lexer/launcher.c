/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:56:21 by tarini            #+#    #+#             */
/*   Updated: 2025/06/23 13:04:31 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	launch_redirect_out(const char *input, size_t *i, t_token **head)
{
	if (input[(*i) + 1] == '>')
	{
		(*i)++;
		if (add_token(head, TOK_APPEND_REDIRECT, ">>") == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else
	{
		if (add_token(head, TOK_REDIRECT_OUT, ">") == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	(*i)++;
	return (RETURN_SUCCESS);
}

static int	launch_redirect_in(const char *input, size_t *i, t_token **head)
{
	if (input[(*i) + 1] == '<')
	{
		(*i)++;
		if (add_token(head, TOK_HEREDOC, "<<") == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else
	{
		if (add_token(head, TOK_REDIRECT_IN, "<") == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	(*i)++;
	return (RETURN_SUCCESS);
}

int	launch_tokens(const char *input, size_t *i, t_token **head)
{
	if (ft_isspace(input[*i]))
		(*i)++;
	else if (input[*i] == '|')
	{
		if (add_token(head, TOK_PIPE, "|") == RETURN_FAILURE)
			return (RETURN_FAILURE);
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		if (launch_redirect_out(input, i, head) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else if (input[*i] == '<')
	{
		if (launch_redirect_in(input, i, head) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else
	{
		if (process_combined_token(input, i, head) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
