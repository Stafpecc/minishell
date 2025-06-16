/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:01:21 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/16 15:06:27 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// need tarini for that case!!!
// TODO? if just export do like bash or follow manual? aka ask for arguments
static int	error_finder(t_command_exec *node)
{
	if (!node->cmd_parts[1])
	{
			ft_printfd("minishell: export: require an argument: \n");
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
static int	equal_sign_case(t_utils *utils, char *cmd)
{
	if (expand_env(utils))
		return (MALLOC_ERROR);
	utils->env[utils->size_env - 1] = ft_strdup(cmd);
	if (!utils->env[utils->size_env - 1])
		return (MALLOC_ERROR);
	return (RETURN_SUCCESS);
}

static int	no_equal_sign_case(t_utils *utils, char *cmd)
{
	if (expand_env(utils))
		return (MALLOC_ERROR);
	utils->env[utils->size_env - 1] = ft_strjoin(cmd, "=");
	if (!utils->env[utils->size_env - 1])
		return (MALLOC_ERROR);
	return (RETURN_SUCCESS);
}

static int	cmd_browser(t_command_exec *node, t_utils *utils, size_t i)
{
	while (node->cmd_parts[i])
	{ 
		if (node->cmd_parts[i][0] == '=' || !ft_isalpha(node->cmd_parts[i][0])
        || !ft_strcmp(&node->cmd_parts[1][0], "_"))
		    ft_printfd("minishell: export: '%s': not a valid identifier\n",
                node->cmd_parts[i]);
		else if (ft_strchr(node->cmd_parts[i], '='))
		{
			if (equal_sign_case(utils, node->cmd_parts[i]))
				return (MALLOC_ERROR);
		}
		else
		{
			if (no_equal_sign_case(utils, node->cmd_parts[i]))
				return (MALLOC_ERROR);
		}
		i++;
	}
	return (RETURN_SUCCESS);
}

int	export_builtin(t_command_exec *node, t_utils *utils)
{
	if (error_finder(node))
		return (RETURN_FAILURE);
	if (cmd_browser(node, utils, 1))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}