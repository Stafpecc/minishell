/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:33:08 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 13:33:29 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "../../../libft/includes/libft.h"

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
