/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_handle_simple.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:50:14 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/20 17:00:38 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "../../../libft/includes/libft.h"

static char	*extract_simple_token(const char *input, size_t start, size_t end)
{
	return (ft_substr(input, start, end - start));
}

static int	add_expanded_tokens(t_token **head, char *expanded)
{
	char	**words;
	int		j;

	words = ft_split(expanded, ' ');
	if (!words)
		return (RETURN_FAILURE);
	j = 0;
	while (words[j])
	{
		if (add_token(head, TOK_WORD, words[j]) == RETURN_FAILURE)
		{
			ft_free_split(words);
			return (RETURN_FAILURE);
		}
		j++;
	}
	ft_free_split(words);
	return (RETURN_SUCCESS);
}

static int	handle_expanded(t_token_ctx *ctx, char *expanded)
{
	int	status;

	status = RETURN_SUCCESS;
	if (add_expanded_tokens(ctx->head, expanded) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	free(expanded);
	free(*(ctx->buffer));
	*(ctx->buffer) = ft_strdup("");
	if (!*(ctx->buffer))
		return (RETURN_FAILURE);
	return (status);
}

static int	append_expanded_to_buffer(char **buffer, char *expanded)
{
	char	*new_buffer;

	new_buffer = strjoin_and_free(*buffer, expanded);
	if (!new_buffer)
	{
		free(expanded);
		return (RETURN_FAILURE);
	}
	*buffer = new_buffer;
	free(expanded);
	return (RETURN_SUCCESS);
}

int	handle_simple_token(t_token_ctx *ctx, t_utils *utils)
{
	size_t	start;
	size_t	end;
	char	*raw;
	bool	was_expanded;
	char	*expanded;

	start = *(ctx->i);
	end = find_simple_token_end(ctx->input, start);
	*(ctx->i) = end;
	raw = extract_simple_token(ctx->input, start, end);
	if (!raw)
		return (RETURN_FAILURE);
	was_expanded = false;
	expanded = expand_variables(raw, utils, &was_expanded);
	free(raw);
	if (!expanded)
		return (RETURN_FAILURE);
	if (was_expanded)
		return (handle_expanded(ctx, expanded));
	else
		return (append_expanded_to_buffer(ctx->buffer, expanded));
}
