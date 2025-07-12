/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:05 by tarini            #+#    #+#             */
/*   Updated: 2025/07/12 14:40:32 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../../../libft/includes/libft.h"

static int process_quoted_token_separate(const char *input, size_t *i, t_token **head, char quote)
{
	size_t start;
	char *buffer;
	int token_type;

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

static char *extract_quoted_part(const char *input, size_t *i, char quote)
{
	size_t start = *i + 1;
	size_t j = start;
	while (input[j] && input[j] != quote)
		j++;
	if (input[j] != quote)
		return NULL;
	char *part = ft_substr(input, start, j - start);
	if (!part)
		return NULL;
	*i = j + 1;
	return part;
}

static char *concat_buffer_part(char *buffer, char *part)
{
	char *tmp = ft_strjoin(buffer, part);
	free(buffer);
	free(part);
	if (!tmp)
		return NULL;
	return tmp;
}

static int handle_quoted_token(const char *input, size_t *i, t_token **head, char quote, char **buffer)
{
	size_t temp_i = *i + 1;
	while (input[temp_i] && input[temp_i] != quote)
		temp_i++;

	if (input[temp_i] != quote)
		return RETURN_FAILURE;

	char next_char = input[temp_i + 1];
	bool next_is_sep = (next_char == '\0' || ft_isspace(next_char) || next_char == '|' || next_char == '<' || next_char == '>');

	if ((*buffer)[0] == '\0' && next_is_sep)
	{
		int status = process_quoted_token_separate(input, i, head, quote);
		if (status == RETURN_FAILURE)
			return RETURN_FAILURE;
	}
	else
	{
		char *part = extract_quoted_part(input, i, quote);
		if (!part)
			return RETURN_FAILURE;
		char *new_buffer = concat_buffer_part(*buffer, part);
		if (!new_buffer)
			return RETURN_FAILURE;
		*buffer = new_buffer;
	}
	return RETURN_SUCCESS;
}

static int handle_simple_token(const char *input, size_t *i, char **buffer)
{
	size_t start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i] != '<' && input[*i] != '>'
		&& input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	char *part = ft_substr(input, start, *i - start);
	if (!part)
		return RETURN_FAILURE;
	char *new_buffer = concat_buffer_part(*buffer, part);
	if (!new_buffer)
		return RETURN_FAILURE;
	*buffer = new_buffer;
	return RETURN_SUCCESS;
}

int process_combined_token(const char *input, size_t *i, t_token **head)
{
	char *buffer = ft_strdup("");
	if (!buffer)
		return RETURN_FAILURE;

	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			int status = handle_quoted_token(input, i, head, input[*i], &buffer);
			if (status == RETURN_FAILURE)
			{
				free(buffer);
				return RETURN_FAILURE;
			}
		}
		else
		{
			int status = handle_simple_token(input, i, &buffer);
			if (status == RETURN_FAILURE)
			{
				free(buffer);
				return RETURN_FAILURE;
			}
		}
	}
	if (buffer[0] != '\0')
	{
		int status = add_token(head, TOK_WORD, buffer);
		free(buffer);
		return status;
	}
	free(buffer);
	return RETURN_SUCCESS;
}
