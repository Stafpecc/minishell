/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:42:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/23 14:52:42 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <stdio.h>

static bool	is_empty_command(t_command *cmd)
{
	return (!cmd || !cmd->cmd_parts || !cmd->cmd_parts[0]);
}

static bool has_conflicting_redirections(t_command *cmd)
{
	return ((cmd->redirect_in && cmd->heredoc) ||
			(cmd->redirect_out && cmd->append_redirections));
}

static int	return_failure(const char *token)
{
	print_syntax_error(token);
	return (RETURN_FAILURE);	
}

void print_syntax_error(const char *token)
{
	ft_printfd("minishell: syntax error near unexpected token `%s'\n", token);
}

int	parse_cmd(t_command *cmd)
{
	t_command *prev = NULL;
	t_command *curr = cmd;

	if (!curr)
		return (RETURN_FAILURE);

	while (curr)
	{
		if (is_empty_command(curr))
			return (return_failure("|"));
		if (has_conflicting_redirections(curr))
			return (return_failure(">"));		
		if ((curr->redirect_in || curr->redirect_out 
			|| curr->append_redirections || curr->heredoc) 
			&& is_empty_command(curr))
			return (return_failure(">"));
		if (prev && is_empty_command(prev) && is_empty_command(curr))
			return (return_failure("|"));
		prev = curr;
		curr = curr->next;
	}
	return (RETURN_SUCCESS);
}
