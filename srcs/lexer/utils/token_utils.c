/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:40:32 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 14:57:03 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "return_error.h"

int	has_only_one_redirection(t_token *head)
{
	if (((head->type == TOK_APPEND_REDIRECT || head->type == TOK_REDIRECT_IN
				|| head->type == TOK_HEREDOC || head->type == TOK_REDIRECT_OUT)
			&& head->next->type == TOK_END))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

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
