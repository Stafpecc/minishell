/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:09 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 11:07:58 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

//	Function to separate properly
//	two case of ENOENT error to send the
//	right msg to the user
static int	enoent_cases(t_command_exec *node, bool execve_failed)
{
	if (errno == ENOENT && !execve_failed)
	{
		join_err_msg_and_write("minishell: ", node->cmd_parts[0],
			": command not found\n");
	}
	else if (execve_failed)
	{
		join_err_msg_and_write("minishell: ", node->cmd_parts[0],
			": No such file or directory\n");
	}
	return (CMD_NOT_FOUND);
}
// depending of the last errno a different msg would be
// used, we close utils and exec and free everything we need
// in utils before exit with the right associated code

void	path_finder_fail(t_command_exec *node, t_utils *utils,
		bool execve_failed, int return_value)
{
	if (errno == ENOENT)
		return_value = enoent_cases(node, execve_failed);
	else if (errno == EACCES)
	{
		join_err_msg_and_write("minishell: ", "permission denied: ",
			node->cmd_parts[0]);
		write(2, "\n", 1);
		return_value = CMD_PERMISSION_DENIED;
	}
	else if (errno == ENOMEM)
	{
		join_err_msg_and_write("minishell: ", node->cmd_parts[0],
			": Malloc failed\n");
		return_value = EXIT_FAILURE;
	}
	free_utils(utils);
	free_commands_exec(node);
	exit(return_value);
}
