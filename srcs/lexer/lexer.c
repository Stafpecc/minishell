/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:34 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 13:51:50 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lexer.h"

t_token *lexer(const char *input)
{
	t_token *head;
	size_t i;

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
