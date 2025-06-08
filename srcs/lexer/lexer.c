/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:34 by tarini            #+#    #+#             */
/*   Updated: 2025/06/08 04:10:24 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lexer.h"

t_token	*lexer(const char *input)
{
	t_token	*head;
	size_t	i;

	if (!input || !*input)
		return (NULL);
	i = 0;
	head = NULL;
	while (input[i])
	{
		if (launch_tokens(input, &i, &head) == RETURN_FAILURE)
			return (NULL);
	}
	if (add_token(&head, TOK_END, "") == RETURN_FAILURE)
		return (NULL);
	return (head);
}
