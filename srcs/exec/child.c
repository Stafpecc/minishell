/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:48:11 by tarini            #+#    #+#             */
/*   Updated: 2025/07/24 18:31:55 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	exit_child_builtin(t_command_exec *node, t_utils *utils)
{
	int	tmp_last_return;

	tmp_last_return = utils->last_return;
	free_utils(utils);
	free_commands_exec(node);
	exit(tmp_last_return);
}

static int	built_in_child(t_command_exec *node, t_utils *utils)
{
	if (!ft_strcmp(node->cmd_parts[0], "cd"))
		utils->last_return = ((cd_builtin(node, utils, 0, 0)));
	else if (!ft_strcmp(node->cmd_parts[0], "echo"))
		utils->last_return = ((echo_builtin(node, TRUE, 1)));
	else if (!ft_strcmp(node->cmd_parts[0], "pwd"))
		utils->last_return = ((pwd_builtin(node)));
	else if (!ft_strcmp(node->cmd_parts[0], "export"))
		utils->last_return = ((export_builtin(node, utils, 1, RETURN_SUCCESS)));
	else if (!ft_strcmp(node->cmd_parts[0], "unset"))
		utils->last_return = ((unset_builtin(node, utils, 0, 0)));
	else if (!ft_strcmp(node->cmd_parts[0], "env"))
		utils->last_return = ((env_builtin(node, utils, 0)));
	else if (!ft_strcmp(node->cmd_parts[0], "exit"))
		utils->last_return = ((exit_builtin(node, utils)));
	exit_child_builtin(node, utils);
	return (0);
}

void	child_redirect(t_command_exec *node, t_utils *utils)
{
	char	*path;

	if (!node->cmd_parts || !node->cmd_parts[0])
		return ;
	if (ft_strchr(node->cmd_parts[0], ' ')
		|| ft_strchr(node->cmd_parts[0], '|'))
	{
		join_err_msg_and_write("minishell: ", node->cmd_parts[0],
			": command not found\n");
		path_finder_fail(node, utils, 42, 127);
	}
	if (built_in_checker(node->cmd_parts[0]))
		built_in_child(node, utils);
	else if (!ft_strchr(node->cmd_parts[0], '/'))
	{
		path = path_finder(utils->env, node->cmd_parts[0], NULL);
		if (path == NULL)
			path_finder_fail(node, utils, 0, 0);
		execve(path, node->cmd_parts, utils->env);
	}
	else
		execve(node->cmd_parts[0], node->cmd_parts, utils->env);
	path_finder_fail(node, utils, 1, 0);
}
