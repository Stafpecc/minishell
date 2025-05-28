/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:42:29 by tarini            #+#    #+#             */
/*   Updated: 2025/05/28 14:01:18 by tarini           ###   ########.fr       */
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

static int	return_failure(const char *token, t_utils *utils)
{
	print_syntax_error(token, utils);
	return (RETURN_FAILURE);	
}

void print_syntax_error(const char *token, t_utils *utils)
{
	utils->last_return = CMD_INVALID_ARGUMENT;
	ft_printfd("minishell: syntax error near unexpected token `%s'\n", token);
}

int	parse_cmd(t_command *cmd, t_utils *utils)
{
	t_command *prev = NULL;
	t_command *curr = cmd;

	if (!curr)
		return (RETURN_FAILURE);

	while (curr)
	{
		if (is_empty_command(curr))
			return (return_failure("|", utils));
		if (has_conflicting_redirections(curr))
			return (return_failure(">", utils));		
		if ((curr->redirect_in || curr->redirect_out 
			|| curr->append_redirections || curr->heredoc) 
			&& is_empty_command(curr))
			return (return_failure(">", utils));
		if (prev && is_empty_command(prev) && is_empty_command(curr))
			return (return_failure("|", utils));
		prev = curr;
		curr = curr->next;
	}
	return (RETURN_SUCCESS);
}
