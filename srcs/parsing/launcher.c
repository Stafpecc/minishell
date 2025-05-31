/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:10:48 by tarini            #+#    #+#             */
/*   Updated: 2025/05/31 13:55:13 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "return_error.h"
#include "../../libft/includes/libft.h"

#include <stdio.h>

int launch_commands(t_token **tokens, t_command **curr, t_command *head, t_utils *utils)
{
	if (is_word_like(*tokens))
	{
		if (process_word_string(tokens, *curr) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else if ((*tokens)->type == TOK_REDIRECT_IN)
	{
		if (process_redirect_in(tokens, *curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else if ((*tokens)->type == TOK_REDIRECT_OUT)
	{
		if (process_redirect_out(tokens, *curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else if ((*tokens)->type == TOK_PIPE)
	{
		if (process_pipe(curr, head) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else if ((*tokens)->type == TOK_HEREDOC)
	{
		if (process_heredoc(tokens, *curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	else if ((*tokens)->type == TOK_APPEND_REDIRECT)
	{
		if (process_append_redirect(tokens, *curr, head, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	*tokens = (*tokens)->next;
	return (RETURN_SUCCESS);
}
