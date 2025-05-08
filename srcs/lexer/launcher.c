/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:56:21 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 15:47:24 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int launch_tokens(const char *input, size_t *i, t_token **head)
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
	}
	else if (input[*i] == '<')
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
	}
	else
	{
		if (process_word_or_string(input, i, head) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
