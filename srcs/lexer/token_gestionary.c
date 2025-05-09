/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_gestionary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:18:32 by tarini            #+#    #+#             */
/*   Updated: 2025/05/04 15:56:19 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "return_error.h"

t_token *create_token(t_token_type type, const char *value)
{
	t_token *token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

int add_token(t_token **head, t_token_type type, const char *value)
{
	t_token *new_token;
	t_token *curr;
	
	new_token = token_create(type, value);
	if (!new_token)
	{
		free_token(*head);
		return (RETURN_FAILURE);
	}
	if (!*head)
	*head = new_token;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new_token;
	}
	return (RETURN_SUCCESS);
}
