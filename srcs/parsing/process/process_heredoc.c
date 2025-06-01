/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:35:58 by tarini            #+#    #+#             */
/*   Updated: 2025/06/01 14:07:09 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_heredoc(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
{
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
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
	//curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}
