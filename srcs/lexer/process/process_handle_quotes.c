/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handle_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:30:12 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 18:19:40 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "../../../libft/includes/libft.h"

static char	*extract_quoted_substring(const char *input, size_t start,
	size_t end)
{
	return (ft_substr(input, start, end - start));
}

static char	*process_quoted_content(char *raw, char quote_char,
	t_utils *utils, bool *was_expanded)
{
	char	*result;

	if (quote_char == '\'')
		result = raw;
	else
		result = expand_variables(raw, utils, was_expanded);
	return (result);
}

static int	append_to_buffer(char **buffer, char *to_append,
	char quote_char, char *raw)
{
	char	*new_buffer;

	new_buffer = strjoin_and_free(*buffer, to_append);
	if (!new_buffer)
	{
		if (quote_char != '\'')
			free(to_append);
		else
			free(raw);
		return (RETURN_FAILURE);
	}
	*buffer = new_buffer;
	if (quote_char != '\'')
		free(to_append);
	return (RETURN_SUCCESS);
}

static char	*get_quoted_content(t_token_ctx *ctx, char quote_char,
	t_utils *utils)
{
	size_t	start;
	size_t	end;
	char	*raw;
	char	*to_append;
	bool	was_expanded;

	start = ++(*ctx->i);
	end == find_closing_quote(ctx->input, start, quote_char);
	if (ctx->input[end] != quote_char)
		return (NULL);
	raw = extract_quoted_substring(ctx->input, start, end);
	if (!raw)
		return (NULL);
	was_expanded = false;
	to_append = process_quoted_content(raw, quote_char, utils, &was_expanded);
	free(raw);
	return (to_append);
}

int	handle_quoted_token(t_token_ctx *ctx, char quote_char, t_utils *utils)
{
	char	*to_append;

	to_append = get_quoted_content(ctx, quote_char, utils);
	if (!to_append)
		return (RETURN_FAILURE);
	if (append_to_buffer(ctx->buffer, to_append, quote_char, NULL)
		== RETURN_FAILURE)
	{
		free(to_append);
		return (RETURN_FAILURE);
	}
	*ctx->i += ft_strlen(to_append) + 2;
	free(to_append);
	return (RETURN_SUCCESS);
}
