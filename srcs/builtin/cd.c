/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:52:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/21 09:25:54 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// function that depending of its parameters will find
// or the line of PWD or OLD_PWD depending of the
// old_or_new parameter

static int	cd_pwd_finder(t_utils *utils, bool old_or_new, int result)
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
// expend env's space for PWD_OLD and NEW and assign it
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
// the emplacement of pwd in the env,
// and the old pwd emplacement as well.
// if pwd and/or old pwd doesnt exist we
// create and fill them during cd
// then we replace old pwd with the actual path we are in
// by getting the actual cwd then join with OLDPWD:
// if everything goes well we return 0 (SUCCESS)

static int	cd_utils_initialization(t_utils *utils, int *pwd_emplacement,
		int *pwd_old_emplacement)
{
	char	*tmp;
	char	*cwd;

	*pwd_emplacement = cd_pwd_finder(utils, NEW, 0);
	*pwd_old_emplacement = cd_pwd_finder(utils, OLD, 0);
	if (*pwd_emplacement == NONE || *pwd_old_emplacement == NONE)
	{
		if (create_pwd_if_none(utils, pwd_emplacement, pwd_old_emplacement))
			return (return_errors(MALLOC_ERROR, ERR_CD_MALLOC, NULL));
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (return_errors(MALLOC_ERROR, ERR_CD_GETCWD, NULL));
	tmp = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	if (!tmp)
		return (return_errors(MALLOC_ERROR, ERR_CD_MALLOC, NULL));
	free(utils->env[*pwd_old_emplacement]);
	utils->env[*pwd_old_emplacement] = tmp;
	return (RETURN_SUCCESS);
}

// Check if we got at least one argument
// check if didnt get more than one argument
// if those check pass the cd function can continue
// to run properly
static int	cd_error_checker(t_command_exec *node)
{
	if (!node->cmd_parts || !node->cmd_parts[0] || !node->cmd_parts[1])
	{
		write(2,
			"minishell: cd: only works with a relative or absolute path \n",
			61);
		return (RETURN_FAILURE);
	}
	if (node->cmd_parts[2])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
// we start by checking if the arg are valids for our cd
// (so basicaly only one arg is valid here)
// then init the right data we require for a successful
// run of the built-in.
// then we search if the dir sent as arg does indeed exist and
// change our emplacement according to if it exist or not
// if it does we update pwd emplacement into the new emplacement path
// and old pwd into the old emplacement path

int	cd_builtin(t_command_exec *node, t_utils *utils, int pwd_emplacement,
		int pwd_old_emplacement)
{
	char	*tmp;
	char	*cwd;

	tmp = NULL;
	cwd = NULL;
	if (cd_error_checker(node))
		return (RETURN_FAILURE);
	if (cd_utils_initialization(utils, &pwd_emplacement, &pwd_old_emplacement))
		return (MALLOC_ERROR);
	if (chdir(node->cmd_parts[1]))
		return (return_errors(RETURN_FAILURE, ERR_CD_CHDIR, node));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (return_errors(MALLOC_ERROR, ERR_CD_GETCWD, node));
	tmp = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!tmp)
		return (return_errors(MALLOC_ERROR, ERR_CD_MALLOC, node));
	free(utils->env[pwd_emplacement]);
	utils->env[pwd_emplacement] = tmp;
	return (RETURN_SUCCESS);
}
