/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:34 by tarini            #+#    #+#             */
/*   Updated: 2025/07/15 21:24:50 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lexer.h"

static void	remove_token(t_token **head, t_token *node_to_remove)
{
	t_token	*curr;
	t_token	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr == node_to_remove)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	remove_empty_tokens(t_token **head)
{
	t_token	*curr;
	t_token	*next;

	if (!head || !*head)
		return ;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		if (curr->value && curr->value[0] == '\0')
			remove_token(head, curr);
		curr = next;
	}
}

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
	remove_empty_tokens(&head);
	if (add_token(&head, TOK_END, "") == RETURN_FAILURE)
		return (NULL);
	return (head);
}
