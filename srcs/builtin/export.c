/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:01:21 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/17 11:05:01 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// compare content of env to check if it hold
// the same name as the concerned arg entered with export

static int	is_variable_already_in_env(t_utils *utils, char *variable_name,
		size_t i, bool is_equal)
{
	while (utils->env[i])
	{
		if (!ft_strncmp(variable_name, utils->env[i], ft_strlen(variable_name)))
		{
			if (is_equal)
				free(variable_name);
			return (i);
		}
		else
			i++;
	}
	if (is_equal)
		free(variable_name);
	return (FALSE);
}
// utils function that isolate the name of the variable
// in case of a cmd with an = sign, for further processing
// in equal_sign_case
// increment index until we get to the =sign, malloc
// enough space to variable_name thanks to that index then fill
// the same variable with the rightful characters then return the result

static char	*assign_variable_name(char *cmd, char *variable_name, size_t i,
		size_t j)
{
	while (cmd[i] != '=')
		i++;
	variable_name = malloc(i + 1 * sizeof(char));
	if (!variable_name)
		return (NULL);
	while (j != i - 1)
	{
		variable_name[j] = cmd[j];
		j++;
	}
	variable_name[j] = '\0';
	return (variable_name);
}
// if no equal sign it mean that the cmd only hold the
// variable's name
// we check if the said env variable already exist
// in the actual env, if it does we get out without doing anything
// if it doesnt we expand env then we add the new variable to it.

static int	no_equal_sign_case(t_utils *utils, char *cmd,
		size_t existing_variable_emp)
{
	existing_variable_emp = is_variable_already_in_env(utils, cmd, 0, FALSE);
	if (!existing_variable_emp)
	{
		if (expand_env(utils))
			return (MALLOC_ERROR);
		utils->env[utils->size_env - 1] = ft_strjoin(cmd, "=");
		if (!utils->env[utils->size_env - 1])
			return (MALLOC_ERROR);
	}
	return (RETURN_SUCCESS);
}

// if equal sign it mean what is at the right side
// is the result of the said variable
// we isolate the name of the variable thanks to assign_variable_name
// we find if the same variable name does already exist in our env
// if it does the content of said variable should be replaced
// else we should expand env size with expand_env then place
// our new variable + content in it
// then get back to the loop in export_builtin function

static int	equal_sign_case(t_utils *utils, char *cmd, char *variable_name,
		int existing_variable_emp)
{
	variable_name = assign_variable_name(cmd, NULL, 0, 0);
	if (!variable_name)
		return (MALLOC_ERROR);
	existing_variable_emp = is_variable_already_in_env(utils, variable_name, 0,
			TRUE);
	if (existing_variable_emp)
	{
		utils->env[existing_variable_emp] = ft_strdup(cmd);
		if (!utils->env[existing_variable_emp])
			return (MALLOC_ERROR);
	}
	else
	{
		if (expand_env(utils))
			return (MALLOC_ERROR);
		utils->env[utils->size_env - 1] = ft_strdup(cmd);
		if (!utils->env[utils->size_env - 1])
			return (MALLOC_ERROR);
	}
	return (RETURN_SUCCESS);
}

// here we gonna check if we do at least have an argument(WIP)
// then we check browse all the args until we reached the end
// we check starting at 1 because 0 hold "export"
// then we check everytime the first character to see if it
// is conform to what an env variable should be named
// if it is the case we check if it hold an = sign
// and goes to the right function depending of if it hold
// the said sign or not (because not same effect expected)
// once we get out of the while loop we return_success

// TODO? if just export do like bash or follow manual? aka ask for arguments

int	export_builtin(t_command_exec *node, t_utils *utils, size_t i)
{
	if (!node->cmd_parts[1])
	{
		ft_printfd("minishell: export: require an argument: \n");
		return (RETURN_FAILURE);
	}
	while (node->cmd_parts[i])
	{
		if (node->cmd_parts[i][0] == '=' || (!ft_isalpha(node->cmd_parts[i][0])
				&& (node->cmd_parts[i][0] != '_')))
			ft_printfd("minishell: export: '%s': not a valid identifier\n",
				node->cmd_parts[i]);
		else if (ft_strchr(node->cmd_parts[i], '='))
		{
			if (equal_sign_case(utils, node->cmd_parts[i], NULL, 0))
				return (MALLOC_ERROR);
		}
		else
		{
			if (no_equal_sign_case(utils, node->cmd_parts[i], 0))
				return (MALLOC_ERROR);
		}
		i++;
	}
	return (RETURN_SUCCESS);
}
