/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:25 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 17:04:28 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_redirect_in(t_token **tokens, t_command *curr, t_command *head)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		free_commands(head);
		return (RETURN_FAILURE);
	}
	curr->redirect_in = ft_strdup((*tokens)->value);
	return (RETURN_SUCCESS);
}

int process_redirect_out(t_token **tokens, t_command *curr, t_command *head)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		free_commands(head);
		return (RETURN_FAILURE);
	}
	curr->redirect_out = ft_strdup((*tokens)->value);
	return (RETURN_SUCCESS);
}

int process_append_redirect(t_token **tokens, t_command *curr, t_command *head)
{
    (*tokens) = (*tokens)->next;

    if (!(*tokens) || !is_word_like(*tokens))
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    if (!curr->append_redirections)
    {
        curr->append_redirections = malloc(sizeof(t_arg));
        if (!curr->append_redirections)
        {
            free_commands(head);
            return (RETURN_FAILURE);
        }
    }
    curr->append_redirections->arg = ft_strdup((*tokens)->value);
    if (!curr->append_redirections->arg)
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    process_quotes_arg(*tokens, curr->append_redirections);

    return (RETURN_SUCCESS);
}
