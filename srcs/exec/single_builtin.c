/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:09:30 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/01 13:33:33 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// if redirection will redirect
// to dup properly, if fail return 1 else 0
static int	single_built_in_redirections(t_command_exec *node)
{
	if (node->redirect_in)
	{
		if (read_dup(node->redirect_in, NONE))
			return (RETURN_FAILURE);
	}
	if (node->redirect_out)
	{
		if (write_dup(node->redirect_out, 0))
		{
			return (RETURN_FAILURE);
		}
	}
	return (RETURN_SUCCESS);
}
// reinitialize by default any change that was done to
// the stdin(0) and (stdout) then return the last return

static int	reinit_fd_return_main(t_command_exec *node, t_utils *utils)
{
	if (node->redirect_in)
	{
		if (dup2(utils->old_stdin, STDIN_FILENO) == -1)
			return (MALLOC_ERROR);
	}
	if (node->redirect_out)
	{
		if (dup2(utils->old_stdout, STDOUT_FILENO) == -1)
			return (MALLOC_ERROR);
	}
	return (utils->last_return);
}

// function that will do the right redirect if needed
// then determine which built-in we are dealing with
// then return the return value of the built-in function

int	single_built_in(t_command_exec *node, t_utils *utils)
{
	if (node->redirect_in || node->redirect_out)
	{
		if (single_built_in_redirections(node))
			return (MALLOC_ERROR);
	}
	if (!ft_strcmp(node->cmd_parts[0], "cd"))
		utils->last_return = (cd_builtin(node, utils, 0, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "echo"))
		utils->last_return = (echo_builtin(node, TRUE, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "pwd"))
		utils->last_return = (pwd_builtin(node, utils, 0, 4));
	else if (!ft_strcmp(node->cmd_parts[0], "export"))
		utils->last_return = (export_builtin(node, utils, 1));
	else if (!ft_strcmp(node->cmd_parts[0], "unset"))
		utils->last_return = (unset_builtin(node, utils));
	else if (!ft_strcmp(node->cmd_parts[0], "env"))
		utils->last_return = (env_builtin(node, utils, 0));
	else if (!ft_strcmp(node->cmd_parts[0], "exit"))
		utils->last_return = (exit_builtin(node, utils));
	return (reinit_fd_return_main(node, utils));
}
