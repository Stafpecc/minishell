/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handle_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:30:12 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/21 10:40:00 by stafpec          ###   ########.fr       */
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
		result = ft_strdup(raw);
	else
		result = expand_variables(raw, utils, was_expanded);
	return (result);
}

static int	append_to_buffer(char **buffer, char *to_append,
	char quote_char, char *raw)
{
	char	*new_buffer;

	new_buffer = strjoin_and_free(*buffer, to_append, true);
	if (!new_buffer)
	{
		if (quote_char != '\'')
			free(to_append);
		else
			free(raw);
		return (RETURN_FAILURE);
	}
	*buffer = new_buffer;
	return (RETURN_SUCCESS);
}

static int	return_free_raw(char *raw)
{
	free(raw);
	return (RETURN_FAILURE);
}

int	handle_quoted_token(t_token_ctx *ctx, char quote_char, t_utils *utils)
{
	size_t	start;
	size_t	end;
	char	*raw;
	char	*to_append;
	bool	was_expanded;

	start = ++(*ctx->i);
	end = find_closing_quote(ctx->input, start, quote_char);
	if (ctx->input[end] != quote_char)
		return (RETURN_FAILURE);
	raw = extract_quoted_substring(ctx->input, start, end);
	if (!raw)
		return (RETURN_FAILURE);
	was_expanded = false;
	to_append = process_quoted_content(raw, quote_char, utils, &was_expanded);
	if (!to_append)
		return (return_free_raw(raw));
	if (append_to_buffer(ctx->buffer, to_append, quote_char, raw)
		== RETURN_FAILURE)
		return (return_free_raw(raw));
	free(raw);
	*ctx->i = end + 1;
	return (RETURN_SUCCESS);
}
