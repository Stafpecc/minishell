/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:42:26 by tarini            #+#    #+#             */
/*   Updated: 2025/07/20 16:46:07 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"

static int	check_start_single_quote(const char *input, size_t i)
{
	if (input[i] != '\'')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static ssize_t	find_closing_single_quote(const char *input, size_t start)
{
	size_t	pos;

	pos = start;
	while (input[pos] && input[pos] != '\'')
		pos++;
	if (input[pos] != '\'')
		return (-1);
	return (pos);
}

static char	*extract_single_quoted_str(const char *input, size_t start,
	size_t end)
{
	return (ft_strndup(&input[start], end - start));
}

static int	append_to_buffer(char **buffer, char *str)
{
	char	*tmp;

	tmp = strjoin_and_free(*buffer, str);
	free(str);
	if (!tmp)
		return (RETURN_FAILURE);
	*buffer = tmp;
	return (RETURN_SUCCESS);
}

int	handle_single_quotes(t_token_ctx *ctx)
{
	const char	*input = ctx->input;
	size_t		*i;
	char		**buffer;
	ssize_t		end;
	char		*raw;

	i = ctx->i;
	buffer = ctx->buffer;
	if (check_start_single_quote(input, *i) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	(*i)++;
	end = find_closing_single_quote(input, *i);
	if (end == -1)
		return (RETURN_FAILURE);
	raw = extract_single_quoted_str(input, *i, end);
	if (!raw)
		return (RETURN_FAILURE);
	if (append_to_buffer(buffer, raw) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	*i = end + 1;
	return (RETURN_SUCCESS);
}
