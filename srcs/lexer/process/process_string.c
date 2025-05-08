/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:20 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 17:26:46 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
