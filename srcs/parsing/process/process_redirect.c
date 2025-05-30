/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:34:25 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 17:06:49 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

int process_redirect_in(t_token **tokens, t_command *curr, t_command *head, t_utils *utils) {
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
	if (!curr->redirect_in)
	{
		curr->redirect_in = malloc(sizeof(t_arg));
		if (!curr->redirect_in)
			return (process_free_exit(head));
	}
	curr->redirect_in->arg = ft_strdup((*tokens)->value);
	if (!curr->redirect_in->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->redirect_in);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

int process_redirect_out(t_token **tokens, t_command *curr, t_command *head, t_utils *utils) {
	(*tokens) = (*tokens)->next;
	if (!(*tokens) || !is_word_like(*tokens))
	{
		if (*tokens && !is_redirect_or_pipe(*tokens))
			print_syntax_error((*tokens)->value, utils);
		else
			print_syntax_error("newline", utils);
		return (process_free_exit(head));
	}
	if (!curr->redirect_out)
	{
		curr->redirect_out = malloc(sizeof(t_arg));
		if (!curr->redirect_out)
			return (process_free_exit(head));
	}
	curr->redirect_out->arg = ft_strdup((*tokens)->value);
	if (!curr->redirect_out->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->redirect_out);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}

int process_append_redirect(t_token **tokens, t_command *curr, t_command *head, t_utils *utils)
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
	if (!curr->append_redirections)
	{
		curr->append_redirections = malloc(sizeof(t_arg));
		if (!curr->append_redirections)
			return (process_free_exit(head));
	}
	curr->append_redirections->arg = ft_strdup((*tokens)->value);
	if (!curr->append_redirections->arg)
		return (process_free_exit(head));
	process_quotes(*tokens, curr->append_redirections);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	curr->cmd_parts = add_argument(curr->cmd_parts, (*tokens)->value);
	(*tokens) = (*tokens)->next;
	return (RETURN_SUCCESS);
}
