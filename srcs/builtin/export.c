/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:01:21 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/17 09:34:30 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static int	no_equal_sign_case(t_utils *utils, char *cmd)
{
	if (expand_env(utils))
		return (MALLOC_ERROR);
	utils->env[utils->size_env - 1] = ft_strjoin(cmd, "=");
	if (!utils->env[utils->size_env - 1])
		return (MALLOC_ERROR);
	return (RETURN_SUCCESS);
}

static int is_variable_already_in_env(t_utils *utils, char *variable_name, int i)
{	
	while(utils->env[i])
	{
		if(!ft_strncmp(variable_name, utils->env[i], ft_strlen(variable_name)))
		{
			free(variable_name);
			return(i);
		}	
		else
			i++;
	}
	free(variable_name);
	return(FALSE);
}

static char *assign_variable_name(char *cmd)
{
	char *variable_name;
	int i;
	int j;
	
	j = 0;
	i = 0;
	while(cmd[i] != '=')
		i++;
	variable_name = malloc(i + 1 * sizeof (char));
	if (!variable_name)
		return(NULL);
	while (j != i - 1)
	{
		variable_name[j] = cmd[j];
		j++;
	}
	variable_name[j] = '\0';
	return(variable_name);
}
static int	equal_sign_case(t_utils *utils, char *cmd, char *variable_name, int existing_variable_emp)
{
	variable_name = assign_variable_name(cmd);
	if(!variable_name)
		return (MALLOC_ERROR);
	existing_variable_emp =	is_variable_already_in_env(utils,variable_name, 0);
	if(existing_variable_emp)
	{
		utils->env[existing_variable_emp] = ft_strdup(cmd);
		if(!utils->env[existing_variable_emp])
			return(MALLOC_ERROR);
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
//  ft_strncmp(node->cmd_parts[i], "_", 1)|| 
static int	cmd_browser(t_command_exec *node, t_utils *utils, size_t i)
{
	while (node->cmd_parts[i])
	{ 
		if (node->cmd_parts[i][0] == '=' || (!ft_isalpha(node->cmd_parts[i][0]) && (node->cmd_parts[i][0] != '_'))
        )
		    ft_printfd("minishell: export: '%s': not a valid identifier\n",
                node->cmd_parts[i]);
		else if (ft_strchr(node->cmd_parts[i], '='))
		{
			if (equal_sign_case(utils, node->cmd_parts[i], NULL, 0))
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

int	export_builtin(t_command_exec *node, t_utils *utils)
{
	if (error_finder(node))
		return (RETURN_FAILURE);
	if (cmd_browser(node, utils, 1))
		return (MALLOC_ERROR);
	return (RETURN_SUCCESS);
}