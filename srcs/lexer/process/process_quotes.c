/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:11:56 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/14 15:33:40 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

int	process_quoted_token_separate(const char *input, size_t *i,
	t_token **head, char quote)
{
	size_t	start;
	char	*buffer;
	int		token_type;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (RETURN_FAILURE);
	buffer = ft_substr(input, start, *i - start);
	if (!buffer)
		return (RETURN_FAILURE);
	if (quote == '"')
		token_type = TOK_DOUBLE_QUOTES;
	else
		token_type = TOK_SINGLE_QUOTES;
	if (add_token(head, token_type, buffer) == RETURN_FAILURE)
	{
		free(buffer);
		return (RETURN_FAILURE);
	}
	free(buffer);
	(*i)++;
	return (RETURN_SUCCESS);
}

static bool	is_separator(char c)
{
	return (c == '\0' || ft_isspace(c) || c == '|' || c == '<' || c == '>');
}

static bool	is_separate_quoted(const char *input, size_t i, char quote,
	char *buffer)
{
	size_t	temp_i;

	temp_i = i + 1;
	while (input[temp_i] && input[temp_i] != quote)
		temp_i++;
	if (input[temp_i] != quote)
		return (false);
	return (buffer[0] == '\0' && is_separator(input[temp_i + 1]));
}

static int	append_quoted_to_buffer(const char *input, size_t *i,
	char quote, char **buffer)
{
	char	*part;
	char	*new_buffer;

	part = extract_quoted_part(input, i, quote);
	if (!part)
		return (RETURN_FAILURE);
	new_buffer = concat_buffer_part(*buffer, part);
	if (!new_buffer)
		return (RETURN_FAILURE);
	*buffer = new_buffer;
	return (RETURN_SUCCESS);
}

int	handle_quoted_token(t_token_ctx *ctx, char quote)
{
	if (is_separate_quoted(ctx->input, *(ctx->i), quote, *(ctx->buffer)))
	{
		if (process_quoted_token_separate(ctx->input, ctx->i, ctx->head, quote)
			== RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else
	{
		if (append_quoted_to_buffer(ctx->input, ctx->i, quote, ctx->buffer)
			== RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
