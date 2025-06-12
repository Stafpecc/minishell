/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:20 by tarini            #+#    #+#             */
/*   Updated: 2025/06/11 15:23:22 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

static int	process_quotes(char quote, char *str, t_token **head)
{
	if (quote == '"')
	{
		if (add_token(head, TOK_DOUBLE_QUOTES, str) == RETURN_FAILURE)
		{
			free(str);
			return (RETURN_FAILURE);
		}
	}
	else if (quote == '\'')
	{
		if (add_token(head, TOK_SINGLE_QUOTES, str) == RETURN_FAILURE)
		{
			free(str);
			return (RETURN_FAILURE);
		}
	}
	else
	{
		if (add_token(head, TOK_STRING, str) == RETURN_FAILURE)
		{
			free(str);
			return (RETURN_FAILURE);
		}
	}
	return (RETURN_SUCCESS);
}

int	process_string(const char *input, size_t *i, t_token **head)
{
	char	quote;
	size_t	start;
	char	*str;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (RETURN_FAILURE);
	str = ft_strndup(input + start, *i - start);
	if (!str)
		return (RETURN_FAILURE);
	if (process_quotes(quote, str, head) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	free(str);
	if (input[*i] == quote)
		(*i)++;
	return (RETURN_SUCCESS);
}
