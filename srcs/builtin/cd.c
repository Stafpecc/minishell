/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/30 14:40:53 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include <limits.h> //TORM

#define OLD 0 //TOMV in built.h
#define NEW 1 //TOMV in built.h

static int	cd_builtin_pwd_finder(t_utils *utils, int old_or_new, int result)
{
	if (old_or_new == NEW)
	{
		while (utils->env[result])
		{
			if (!ft_strncmp(utils->env[result], "PWD=", 4))
				return (result);
			result++;
		}
	}
	else if (old_or_new == OLD)
	{
		while (utils->env[result])
		{
			if (!ft_strncmp(utils->env[result], "OLDPWD=", 7))
				return (result);
			result++;
		}
	}
	return (-42);
}

static int	cd_utils_initialization(t_utils *utils, int *pwd_emplacement,
		int *pwd_old_emplacement)
{
	*pwd_emplacement = cd_builtin_pwd_finder(utils, NEW, 0);
	*pwd_old_emplacement = cd_builtin_pwd_finder(utils, OLD, 0);
	if (*pwd_emplacement == -42 || *pwd_old_emplacement == -42)
	{
		// TODO build PWD if missing ask theo about creating new line
	}
	utils->env[*pwd_old_emplacement] = getcwd(NULL, 0); // secure
	if (utils->env[*pwd_old_emplacement])
	{
		utils->env[*pwd_old_emplacement] = ft_strjoin("OLDPWD: ",
				utils->env[*pwd_old_emplacement]); // SECURE
	}
	if (!utils->env[*pwd_old_emplacement])
	{
		perror("getcwd() error");
		return (-42);
	}
	return (EXIT_SUCCESS);
}
static int	cd_error_checker(t_command_exec *node)
{
	if (!node->cmd_parts || !node->cmd_parts[0] || !node->cmd_parts[1])
	{
		ft_printfd("minishell: cd: works with only a relative or absolute path\n");
		return (EXIT_FAILURE);
	}
	if (node->cmd_parts[2])
	{
		ft_printfd("minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cd_builtin(t_command_exec *node, t_utils *utils, int pwd_emplacement,
		int pwd_old_emplacement)
{
	if (cd_utils_initialization(utils, &pwd_emplacement, &pwd_old_emplacement))
		return (EXIT_FAILURE);
	if (cd_error_checker(node))
		return (EXIT_FAILURE);
	if (chdir(node->cmd_parts[1]))
	{
		ft_printfd("minishell: cd: %s: ", node->cmd_parts[1]);
		perror("");
		return (EXIT_FAILURE);
	}
	utils->env[pwd_emplacement] = getcwd(NULL, 0);
	if (utils->env[pwd_emplacement])
	{
		utils->env[pwd_emplacement] = ft_strjoin("PWD= ",
				utils->env[pwd_emplacement]);
	}
	if (!utils->env[pwd_emplacement])
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
	ft_printfd("Current working directory: %s\n", utils->env[pwd_emplacement]); //TORM
	ft_printfd("%s\n", utils->env[pwd_old_emplacement]); //TORM
	return (EXIT_SUCCESS);
}
