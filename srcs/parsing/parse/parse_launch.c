/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:33:08 by tarini            #+#    #+#             */
/*   Updated: 2025/07/16 14:55:24 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../../libft/includes/libft.h"

static int	check_redirect_in(char *filename, bool is_heredoc)
{
	if (is_heredoc)
		return (RETURN_SUCCESS);
	if (access(filename, F_OK) == -1) //TODO bug here, check redirection page at Notion.so
	{
		ft_printfd("minisell: %s: No such file or directory\n", filename); 
		return (RETURN_FAILURE);
	}
	if (access(filename, R_OK) == -1)
	{
		ft_printfd("minishell: %s: Permission denied\n", filename);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	handle_redirect_in(t_command *curr, t_utils *utils)
{
	int	i;

	if (!curr->redirect_in)
		return (RETURN_SUCCESS);
	i = 0;
	while (curr->redirect_in[i])
	{
		if (check_redirect_in(curr->redirect_in[i]->arg,
				curr->redirect_in[i]->heredoc) == RETURN_FAILURE)
		{
			utils->last_return = 1;
			return (RETURN_FAILURE);
		}
		i++;
	}
	return (RETURN_SUCCESS);
}

static int	validate_command(t_command *prev, t_command *curr, t_utils *utils)
{
	if (is_empty_command(curr))
		return (return_failure("|", utils));
	if ((curr->redirect_in || curr->redirect_out)
		&& is_empty_command(curr))
		return (return_failure(">", utils));
	if (prev && is_empty_command(prev) && is_empty_command(curr))
		return (return_failure("|", utils));
	if (curr->cmd_parts && curr->cmd_parts[0] && curr->cmd_parts[0]->arg)
	{
		if (parse_directory(curr, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	parse_cmd_helper(t_command *prev, t_command *curr, t_utils *utils)
{
	if (handle_redirect_in(curr, utils) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	return (validate_command(prev, curr, utils));
}

/*
Function that:
- iterates through a linked list of commands (t_command) to validate
their syntax and redirections;
- performs several checks: empty command, conflicting or redundant 
redirections, or redirections to invalid files/directories;
- returns RETURN_FAILURE as soon as a problem is detected,
otherwise RETURN_SUCCESS if everything is correct.
*/
int	parse_cmd(t_command *cmd, t_utils *utils)
{
	t_command	*prev;
	t_command	*curr;

	prev = NULL;
	curr = cmd;
	if (!curr)
		return (RETURN_FAILURE);
	while (curr)
	{
		if (parse_cmd_helper(prev, curr, utils) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		prev = curr;
		curr = curr->next;
	}
	return (RETURN_SUCCESS);
}
