/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:58 by tarini            #+#    #+#             */
/*   Updated: 2025/05/08 17:32:09 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_heredoc(t_token **tokens, t_command *curr, t_command *head)
{
    (*tokens) = (*tokens)->next;
    if (!(*tokens) || !is_word_like(*tokens))
    {
        free_commands(head);
        return (RETURN_FAILURE);
    }
    if (!curr->heredoc)
    {
        curr->heredoc = malloc(sizeof(t_arg));
        if (!curr->heredoc)
        {
            free_commands(head);
            return (RETURN_FAILURE);
        }
    }
    curr->heredoc->arg = ft_strdup((*tokens)->value);
    if (!curr->heredoc->arg)
    {
        free_commands(head);
        return (RETURN_FAILURE);
	}
    process_quotes_arg(*tokens, curr->heredoc);
    return (RETURN_SUCCESS);
}
