/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:20:26 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 16:40:39 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"
#include "parsing.h"

static char	*init_buffer(void)
{
	char	*buffer;

	buffer = ft_strdup("");
	return (buffer);
}

static int	process_token_chars(const char *input, t_token_ctx *ctx,
	t_utils *utils)
{
	int	status;

	status = RETURN_SUCCESS;
	while (input[*ctx->i] && !ft_isspace(input[*ctx->i])
		&& input[*ctx->i] != '|' && input[*ctx->i] != '<'
		&& input[*ctx->i] != '>')
	{
		if (input[*ctx->i] == '"' || input[*ctx->i] == '\'')
			status = handle_quoted_token(ctx, input[*ctx->i], utils);
		else
			status = handle_simple_token(ctx, utils);
		if (status == RETURN_FAILURE)
			break ;
	}
	return (status);
}

int	process_combined_token(const char *input, size_t *i,
	t_token **head, t_utils *utils)
{
	char		*buffer;
	int			status;
	t_token_ctx	ctx;

	buffer = init_buffer();
	if (!buffer)
		return (RETURN_FAILURE);
	ctx.input = input;
	ctx.i = i;
	ctx.head = head;
	ctx.buffer = &buffer;
	ctx.in_single_quote = false;
	ctx.in_double_quote = false;
	ctx.was_expanded = false;
	status = process_token_chars(input, &ctx, utils);
	if (status == RETURN_FAILURE)
	{
		free(buffer);
		return (RETURN_FAILURE);
	}
	status = add_token(head, TOK_WORD, buffer);
	free(buffer);
	return (status);
}
