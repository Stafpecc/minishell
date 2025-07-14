/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:01:21 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/14 15:00:45 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"
#include "parsing.h"
#include "return_error.h"

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
		free(utils->env[existing_variable_emp]);
		utils->env[existing_variable_emp] = ft_strdup(cmd);
		if (!utils->env[existing_variable_emp])
			return (MALLOC_ERROR);
	}
	else
	{
		if (expand_env(utils))
			return (MALLOC_ERROR);
		if (utils->env[utils->size_env - 1])
			free(utils->env[utils->size_env - 1]);
		utils->env[utils->size_env - 1] = ft_strdup(cmd);
		if (!utils->env[utils->size_env - 1])
			return (MALLOC_ERROR);
	}
	return (RETURN_SUCCESS);
}

//if no args are provided then we print on the stdout
//the env in the way that bash does
//including the variables that doesnt have any values yet
static int	no_args_case(t_utils *utils, size_t i, size_t j, bool empty_value)
{
	while (utils->env[i])
	{
		ft_printf("declare -x ");
		while (utils->env[i][j])
		{
			ft_printf("%c", utils->env[i][j]);
			if (utils->env[i][j] == '=')
			{
				ft_printf("\"");
				empty_value = FALSE;
			}
			j++;
		}
		if (!empty_value)
			ft_printf("\"");
		empty_value = TRUE;
		ft_printf("\n");
		j = 0;
		i++;
	}
	return (RETURN_SUCCESS);
}

static int	no_equal_sign_case(t_utils *utils, char *cmd,
		size_t existing_variable_emp)
{
	existing_variable_emp = is_variable_already_in_env(utils, cmd, 0, FALSE);
	if (!existing_variable_emp)
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
//chiffre lettre underscore
static int	error_checker(t_command_exec *node, size_t i)
{
	size_t	j;

	j = 0;
	if (node->cmd_parts[i][0] == '=' || (!ft_isalpha(node->cmd_parts[i][0])
			&& (node->cmd_parts[i][0] != '_')))
	{
		return (RETURN_FAILURE);
	}
	while ((node->cmd_parts[i][j] != '=' && node->cmd_parts[i][j]))
	{
		if (!ft_isalnum(node->cmd_parts[i][j]) && node->cmd_parts[i][j] != '_')
			return (RETURN_FAILURE);
		j++;
	}
	return (RETURN_SUCCESS);
}

int	export_builtin(t_command_exec *node, t_utils *utils, size_t i,
		int return_value)
{
	if (!node->cmd_parts[1])
		return (no_args_case(utils, 0, 0, TRUE));
	while (node->cmd_parts[i])
	{
		if (error_checker(node, i))
		{
			ft_printfd("minishell: export: '%s': not a valid identifier\n",
				node->cmd_parts[i]);
			return_value = RETURN_FAILURE;
		}
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
	return (return_value);
}
