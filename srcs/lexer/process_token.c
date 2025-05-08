/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:56:21 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 14:17:59 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "return_error.h"

int process_string(const char *input, size_t *i, t_token **head)
{
    char quote;
    size_t start;
    char *str;

    quote = input[*i];
    (*i)++;
    start = *i;
    while (input[*i] && input[*i] != quote)
        (*i)++;
    if (input[*i] != quote)
        return (RETURN_FAILURE);
    str = ft_strndup(input + start, *i - start);
    if (!str)
        return (RETURN_FAILURE);
    if (quote == '"')
    {
        if (add_token(head, TOK_DOUBLE_QUOTES, str) == RETURN_FAILURE)
        {
            free(str);
            return (RETURN_FAILURE);
        }
    }
    else if (quote == '\'')
    {
        if (add_token(head, TOK_SINGLE_QUOTES, str) == RETURN_FAILURE)
        {
            free(str);
            return (RETURN_FAILURE);
        }
    }
	else
	{
		if (add_token(head, TOK_STRING, str) == RETURN_FAILURE)
		{
			free(str);
			return (RETURN_FAILURE);
		}
	}
    free(str);
    if (input[*i] == quote)
        (*i)++;
    return (RETURN_SUCCESS);
}

int process_word(const char *input, size_t *i, t_token **head)
{
	size_t start;
	char *str;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' 
		&& input[*i] != '>' && input[*i] != '<')
		(*i)++;
	str = ft_strndup(input + start, *i - start);
	if (!str || add_token(head, TOK_WORD, str) == RETURN_FAILURE)
	{
		free(str);
		return (RETURN_FAILURE);
	}
	free(str);
	return (RETURN_SUCCESS);
}

int process_word_or_string(const char *input, size_t *i, t_token **head)
{
	if (input[*i] == '"' || input[*i] == '\'')
		return (process_string(input, i, head));
	else
		return (process_word(input, i, head));
}

int process_token(const char *input, size_t *i, t_token **head)
{
	if (ft_isspace(input[*i]))
		(*i)++;
	else if (input[*i] == '|')
	{
		if (add_token(head, TOK_PIPE, "|") == RETURN_FAILURE)
			return (RETURN_FAILURE);
		(*i)++;
	}
	else if (input[*i] == '>')
	{
		if (input[(*i) + 1] == '>')
		{
			(*i)++;
			if (add_token(head, TOK_APPEND_REDIRECT, ">>") == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else
		{
			if (add_token(head, TOK_REDIRECT_OUT, ">") == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		if (input[(*i) + 1] == '<')
		{
			(*i)++;
			if (add_token(head, TOK_HEREDOC, "<<") == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		else
		{
			if (add_token(head, TOK_REDIRECT_IN, "<") == RETURN_FAILURE)
				return (RETURN_FAILURE);
		}
		(*i)++;
	}
	else
	{
		if (process_word_or_string(input, i, head) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
