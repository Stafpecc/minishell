/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:42:26 by tarini            #+#    #+#             */
/*   Updated: 2025/07/19 20:52:59 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"

int	handle_single_quotes(t_token_ctx *ctx)
{
	const char	*input = ctx->input;
	size_t		*i;
	char		**buffer;
	size_t		start;
	char		*raw;
	char		*tmp;

	i = ctx->i;
	buffer = ctx->buffer;
	if (input[*i] != '\'')
		return (RETURN_FAILURE);
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (input[*i] != '\'')
		return (RETURN_FAILURE);
	raw = ft_strndup(&input[start], *i - start);
	if (!raw)
		return (RETURN_FAILURE);
	tmp = strjoin_and_free(*buffer, raw);
	free(raw);
	if (!tmp)
		return (RETURN_FAILURE);
	*buffer = tmp;
	(*i)++;
	return (RETURN_SUCCESS);
}

int	handle_double_quotes_with_expansion(t_token_ctx *ctx, t_utils *utils)
{
	const char	*input = ctx->input;
	size_t		*i;
	char		**buffer;
	size_t		start;
	char		*raw;
	bool		was_expanded;
	char		*expanded;
	char		*tmp;

	i = ctx->i;
	buffer = ctx->buffer;
	start = *i + 1;
	(*i)++;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	if (input[*i] != '"')
		return (RETURN_FAILURE);
	raw = ft_strndup(&input[start], *i - start);
	if (!raw)
		return (RETURN_FAILURE);
	was_expanded = false;
	expanded = expand_variables(raw, utils, &was_expanded);
	free(raw);
	if (!expanded)
		return (RETURN_FAILURE);
	tmp = strjoin_and_free(*buffer, expanded);
	free(expanded);
	if (!tmp)
		return (RETURN_FAILURE);
	*buffer = tmp;
	(*i)++;
	return (RETURN_SUCCESS);
}
