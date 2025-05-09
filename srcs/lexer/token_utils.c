/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:40:32 by tarini            #+#    #+#             */
/*   Updated: 2025/05/04 16:06:25 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "return_error.h"

int has_word_token(t_token *head)
{
	while (head)
	{
		if (head->type == TOK_WORD || head->type == TOK_STRING)
			return (RETURN_FAILURE);
		head = head->next;
	}
	return (RETURN_SUCCESS);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t len;
	char *dup;
	size_t i;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[len] && len < n)
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}
