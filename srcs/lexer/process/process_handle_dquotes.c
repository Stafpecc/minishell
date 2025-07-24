/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handle_dquotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:45:30 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/21 09:50:53 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "../../../libft/includes/libft.h"

static int	find_closing_double_quote(const char *input, size_t *i)
{
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] != '"')
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static char	*extract_raw_string(const char *input, size_t start, size_t end)
{
	return (ft_strndup(&input[start], end - start));
}

static char	*expand_raw_string(char *raw, t_utils *utils, bool *was_expanded)
{
	char	*expanded;

	expanded = expand_variables(raw, utils, was_expanded);
	free(raw);
	return (expanded);
}

static int	append_expanded_to_buffer(char **buffer, char *expanded)
{
	char	*tmp;

	tmp = strjoin_and_free(*buffer, expanded, false);
	free(expanded);
	if (!tmp)
		return (RETURN_FAILURE);
	*buffer = tmp;
	return (RETURN_SUCCESS);
}

int	handle_double_quotes_with_expansion(t_token_ctx *ctx, t_utils *utils)
{
	size_t	start;
	char	*raw;
	bool	was_expanded;
	char	*expanded;

	start = *(ctx->i) + 1;
	(*(ctx->i))++;
	if (find_closing_double_quote(ctx->input, ctx->i) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	raw = extract_raw_string(ctx->input, start, *(ctx->i));
	if (!raw)
		return (RETURN_FAILURE);
	was_expanded = false;
	expanded = expand_raw_string(raw, utils, &was_expanded);
	if (!expanded)
		return (RETURN_FAILURE);
	if (append_expanded_to_buffer(ctx->buffer, expanded) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	(*(ctx->i))++;
	return (RETURN_SUCCESS);
}
