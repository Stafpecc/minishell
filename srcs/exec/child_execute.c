/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:09 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/26 14:11:03 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// close old stdin and out and free the env before free utils
void	close_free_utils(t_utils *utils, size_t i)
{
	if (utils)
	{
		close(utils->old_stdin);
		close(utils->old_stdout);
		if (utils->env)
		{
			while (utils->env[i])
			{
				free(utils->env[i]);
				utils->env[i] = NULL;
				i++;
			}
			free(utils->env);
		}
	}
	free(utils);
}

// close cmd_parts in each node and the nodes
void	close_t_command_exec(t_command_exec *node, t_command_exec *tmp,
		size_t i)
{
	if (node)
	{
		while (node)
		{
			i = 0;
			while (node->cmd_parts[i])
			{
				free(node->cmd_parts[i]);
				node->cmd_parts[i] = NULL;
				i++;
			}
			free(node->cmd_parts);
			tmp = node;
			node = node->next;
			free(tmp);
		}
	}
}
// depending of the last errno a different msg would be
// used, we close utils and exec and free everything we need
// in utils before exit with the right associated code

void	path_finder_fail(t_command_exec *node, t_utils *utils)
{
	if (errno == ENOENT)
	{
		ft_printfd("minishell: %s: command not found\n", node->cmd_parts[0]);
		close_free_utils(utils, 0);
		close_t_command_exec(node, NULL, 0);
		exit(CMD_NOT_FOUND);
	}
	else if (errno == EACCES)
	{
		ft_printfd("minishell: permission denied: %s\n", node->cmd_parts[0]);
		close_free_utils(utils, 0);
		close_t_command_exec(node, NULL, 0);
		exit(CMD_PERMISSION_DENIED);
	}
	else if (errno == ENOMEM)
	{
		ft_printfd("minishell: %s: malloc failed\n", node->cmd_parts[0]);
		close_free_utils(utils, 0);
		close_t_command_exec(node, NULL, 0);
		exit(EXIT_FAILURE);
	}
}
