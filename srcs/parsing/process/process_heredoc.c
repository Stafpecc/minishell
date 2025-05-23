/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:58 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 15:15:48 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_heredoc(t_token **tokens, t_command *curr, t_command *head)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
		return (process_free_exit(head));
	if (!curr->heredoc)
	{
		curr->heredoc = malloc(sizeof(t_arg));
		if (!curr->heredoc)
			return (process_free_exit(head));
	}
	curr->heredoc->arg = ft_strdup((*tokens)->value);
	if (!curr->heredoc->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->heredoc);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	return (RETURN_SUCCESS);
}
