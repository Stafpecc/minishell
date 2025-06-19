/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/19 16:46:21 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

#define OLD 0 // TOMV in built.h
#define NEW 1 // TOMV in built.h

// function that depending of its parameters will find
// or the line of PWD or OLD_PWD depending of the
// old_or_new parameter
static int	cd_builtin_pwd_finder(t_utils *utils, bool old_or_new, int result)
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
	return (NONE);
}
// create space for PWD_OLD and NEW and assign it
// to pwd_emplacement and old emplacement
static int	create_pwd_if_none(t_utils *utils, int *pwd_emplacement,
		int *pwd_old_emplacement)
{
	if (*pwd_old_emplacement == NONE)
	{
		if (expand_env(utils))
			return (MALLOC_ERROR);
		*pwd_old_emplacement = utils->size_env - 1;
	}
	if (*pwd_emplacement == NONE)
	{
		if (expand_env(utils))
			return (MALLOC_ERROR);
		*pwd_emplacement = utils->size_env - 1;
	}
	return (RETURN_SUCCESS);
}
// we init what would be usefull to us during cd as
// the emplacementof pwd in the env,
// and the old pwd emplacement as well.
// if pwd and/or old pwd doesnt exist we
// create them in another function
// then we replace old pwd with the actual path we are in
// by getting the actual cwd then join with OLDPWD:
// if everything went well we return 0 (SUCCESS)
static int	cd_utils_initialization(t_utils *utils, int *pwd_emplacement,
		int *pwd_old_emplacement)
{
	*pwd_emplacement = cd_builtin_pwd_finder(utils, NEW, 0);
	*pwd_old_emplacement = cd_builtin_pwd_finder(utils, OLD, 0);
	char *tmp;
	char *cwd;
	
	if (*pwd_emplacement == NONE || *pwd_old_emplacement == NONE)
	{
		if (create_pwd_if_none(utils, pwd_emplacement, pwd_old_emplacement))
			return (return_errors(MALLOC_ERROR, ERR_CD_MALLOC));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return(return_errors(MALLOC_ERROR,ERR_CD_GETCWD));
	tmp = ft_strjoin("OLDPWD=",
			cwd);
	free(cwd);
	if (!tmp)
		return(return_error(MALLOC_ERROR, ERR_CD_MALLOC));
	free(utils->env[*pwd_old_emplacement]);
	utils->env[*pwd_old_emplacement] = tmp;
	return (RETURN_SUCCESS);
}

// Check if we got at least one argument
// check if didnt get more than one argument
static int	cd_error_checker(t_command_exec *node)
{
	if (!node->cmd_parts || !node->cmd_parts[0] || !node->cmd_parts[1])
	{
		ft_printfd("minishell: cd: works with only a relative or absolute path\n");
		return (RETURN_FAILURE);
	}
	if (node->cmd_parts[2])
	{
		ft_printfd("minishell: cd: too many arguments\n");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
// we start by checking if the args are valids for our cd
// then init what we need during CD
// then we search if the dir does indeed exist and
// change our emplacement
// if it does we update pwd emplacement into the new emplacement path
int	cd_builtin(t_command_exec *node, t_utils *utils, int pwd_emplacement,
		int pwd_old_emplacement)
{
	if (cd_error_checker(node))
		return (RETURN_FAILURE);
	if (cd_utils_initialization(utils, &pwd_emplacement, &pwd_old_emplacement))
		return (MALLOC_ERROR);
	if (chdir(node->cmd_parts[1]))
		return(return_errors(RETURN_FAILURE,ERR_CD_CHDIR));
	utils->env[pwd_emplacement] = getcwd(NULL, 0);
	if (utils->env[pwd_emplacement])
	{
		utils->env[pwd_emplacement] = ft_strjoin("PWD=",
				utils->env[pwd_emplacement]);
	}
	if (!utils->env[pwd_emplacement])
		return (return_errors(MALLOC_ERROR, ERR_CD_GETCWD));
	return (RETURN_SUCCESS);
}
