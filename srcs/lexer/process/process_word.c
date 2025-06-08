/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:46:08 by tarini            #+#    #+#             */
/*   Updated: 2025/06/08 04:16:10 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	process_word(const char *input, size_t *i, t_token **head)
{
	size_t	start;
	char	*str;

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
