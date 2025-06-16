/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:05 by tarini            #+#    #+#             */
/*   Updated: 2025/06/16 15:55:38 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

static int	ret_free(char *buffer, bool success)
{
	free(buffer);
	if (success == true)
		return (RETURN_SUCCESS);
	return (RETURN_FAILURE);
}

static int	parse_normal_part(const char *input, size_t *i, char **buffer)
{
	size_t	start;
	char	*part;
	char	*tmp;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '"' && input[*i] != '\''
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
		(*i)++;
	part = ft_substr(input, start, *i - start);
	if (!part)
		return (RETURN_FAILURE);
	tmp = ft_strjoin(*buffer, part);
	free(*buffer);
	free(part);
	if (!tmp)
		return (RETURN_FAILURE);
	*buffer = tmp;
	return (RETURN_SUCCESS);
}

static int	parse_quoted_part(const char *input, size_t *i, char **buffer)
{
	size_t	start;
	char	quote;
	char	*part;
	char	*tmp;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
	}
	if (input[*i] != quote)
		return (RETURN_FAILURE);
	part = ft_substr(input, start, *i - start);
	if (!part)
		return (RETURN_FAILURE);
	tmp = ft_strjoin(*buffer, part);
	free(*buffer);
	free(part);
	if (!tmp)
		return (RETURN_FAILURE);
	*buffer = tmp;
	(*i)++;
	return (RETURN_SUCCESS);
}

int	process_combined_token(const char *input, size_t *i, t_token **head)
{
	char	*buffer;
	int		status;

	buffer = ft_strdup("");
	if (!buffer)
		return (RETURN_FAILURE);
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			status = parse_quoted_part(input, i, &buffer);
			if (status == RETURN_FAILURE)
				return (ret_free(buffer, false));
		}
		else
		{
			status = parse_normal_part(input, i, &buffer);
			if (status == RETURN_FAILURE)
				return (ret_free(buffer, false));
		}
	}
	if (add_token(head, TOK_WORD, buffer) == RETURN_FAILURE)
		return (ret_free(buffer, false));
	return (ret_free(buffer, true));
}
