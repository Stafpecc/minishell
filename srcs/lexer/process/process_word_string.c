/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:05 by tarini            #+#    #+#             */
/*   Updated: 2025/06/26 15:17:14 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

static int	process_normal_word(const char *input, size_t *i, t_token **head)
{
	size_t	start;
	char	*buffer;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	buffer = ft_substr(input, start, *i - start);
	if (!buffer)
		return (RETURN_FAILURE);
	if (add_token(head, TOK_WORD, buffer) == RETURN_FAILURE)
	{
		free(buffer);
		return (RETURN_FAILURE);
	}
	free(buffer);
	return (RETURN_SUCCESS);
}

static int	process_double_quote(const char *input, size_t *i, t_token **head)
{
	size_t	start;
	char	*buffer;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] != '"')
		return (RETURN_FAILURE);
	buffer = ft_substr(input, start, *i - start);
	if (!buffer)
		return (RETURN_FAILURE);
	if (add_token(head, TOK_DOUBLE_QUOTES, buffer) == RETURN_FAILURE)
	{
		free(buffer);
		return (RETURN_FAILURE);
	}
	free(buffer);
	(*i)++;
	return (RETURN_SUCCESS);
}

static int	process_single_quote(const char *input, size_t *i, t_token **head)
{
	size_t	start;
	char	*buffer;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
		return (RETURN_FAILURE);
	buffer = ft_substr(input, start, *i - start);
	if (!buffer)
		return (RETURN_FAILURE);
	if (add_token(head, TOK_SINGLE_QUOTES, buffer) == RETURN_FAILURE)
	{
		free(buffer);
		return (RETURN_FAILURE);
	}
	free(buffer);
	(*i)++;
	return (RETURN_SUCCESS);
}

int	process_combined_token(const char *input, size_t *i, t_token **head)
{
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '\'')
		{
			if (process_single_quote(input, i, head) == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else if (input[*i] == '"')
		{
			if (process_double_quote(input, i, head) == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else
		{
			if (process_normal_word(input, i, head) == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
	}
	return (RETURN_SUCCESS);
}
