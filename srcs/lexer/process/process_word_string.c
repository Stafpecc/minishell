/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:20:26 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 15:02:12 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

char	*extract_quoted_part(const char *input, size_t *i, char quote)
{
	size_t	start;
	size_t	j;
	char	*part;

	start = *i + 1;
	j = start;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] != quote)
		return (NULL);
	part = ft_substr(input, start, j - start);
	if (!part)
		return (NULL);
	*i = j + 1;
	return (part);
}

char	*concat_buffer_part(char *buffer, char *part)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, part);
	free(buffer);
	free(part);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static int	handle_simple_token(const char *input, size_t *i, char **buffer)
{
	size_t	start;
	char	*part;
	char	*new_buffer;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i]
		!= '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	part = ft_substr(input, start, *i - start);
	if (!part)
		return (RETURN_FAILURE);
	new_buffer = concat_buffer_part(*buffer, part);
	if (!new_buffer)
	{
		free(part);
		return (RETURN_FAILURE);
	}
	*buffer = new_buffer;
	return (RETURN_SUCCESS);
}

static int	return_free(char *str)
{
	free(str);
	return (RETURN_FAILURE);
}

int	process_combined_token(const char *input, size_t *i, t_token **head)
{
	char		*buffer;
	int			status;
	t_token_ctx	ctx;

	buffer = ft_strdup("");
	if (!buffer)
		return (RETURN_FAILURE);
	ctx.input = input;
	ctx.i = i;
	ctx.head = head;
	ctx.buffer = &buffer;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '"' || input[*i] == '\'')
			status = handle_quoted_token(&ctx, input[*i]);
		else
			status = handle_simple_token(input, i, &buffer);
		if (status == RETURN_FAILURE)
			return (return_free(buffer));
	}
	status = add_token(head, TOK_WORD, buffer);
	free(buffer);
	return (status);
}
