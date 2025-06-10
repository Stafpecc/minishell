/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:36:53 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/10 14:51:08 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// Just check if the cmd we are dealing with are a built-in cmd or not
// if yes return TRUE if no return FALSE

bool	built_in_checker(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	else
		return (false);
}

// To count how much commands has been sent
// return the value of how much cmd
// in the user's input
int	count_commands(t_command_exec *cmds)
{
	int counter_cmd;

	counter_cmd = 0;
	while (cmds)
	{
		counter_cmd++;
		cmds = cmds->next;
	}
	return (counter_cmd);
}