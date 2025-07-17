/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:11:47 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 10:32:45 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// Just check if the cmd we are dealing with are 
// a built-in cmd or not
// if yes return TRUE if no return FALSE

bool	built_in_checker(char *cmd)
{
	if (!cmd || !cmd[0])
		return (FALSE);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo"))
		return (TRUE);
	else
		return (FALSE);
}

// To count how much commands has been sent
// return the value of how much cmd
// in the user's input

int	count_commands(t_command_exec *cmds)
{
	int	counter_cmd;

	counter_cmd = 0;
	while (cmds)
	{
		counter_cmd++;
		cmds = cmds->next;
	}
	return (counter_cmd);
}
// return the total size of len

size_t	ft_env_len(char **env)
{
	size_t	len;

	len = 0;
	while (env && env[len])
		len++;
	return (len);
}
// we catch the actual len of env store it in old_size
// we add + 2 (one for the new slot and another one for the NULL)
// bcs ft_env_len stop at NULL and we need space for NULL
// we copy the content in ft_realloc then we assign the
// NULL pointers for the new entry and its end
// assign env then return success

int	expand_env(t_utils *utils)
{
	size_t	old_env_size;
	size_t	new_env_size;
	char	**new_env;

	old_env_size = utils->size_env;
	new_env_size = old_env_size + 2;
	new_env = ft_realloc(utils->env, sizeof(char *) * old_env_size,
			sizeof(char *) * new_env_size);
	if (!new_env)
		return (MALLOC_ERROR);
	new_env[old_env_size] = NULL;
	new_env[old_env_size + 1] = NULL;
	utils->size_env += 1;
	utils->env = new_env;
	return (RETURN_SUCCESS);
}

// we catch the actual len of env to store it in old_size
// we also create new_env_size that is old_env_size - 1
// bcs we plan to remove a line in env
// we realloc the new size in new_env thanks to ft_realloc
// then set the last slot at NULL remove 1 to the size_env
// and we change the pointer of env to new env before returning success

// TODO do Ineed to free utils->env before that?

int	condense_env(t_utils *utils)
{
	size_t	old_env_size;
	size_t	new_env_size;
	char	**new_env;

	old_env_size = utils->size_env;
	new_env_size = old_env_size - 1;
	new_env = ft_realloc(utils->env, sizeof(char *) * new_env_size,
			sizeof(char *) * old_env_size);
	if (!new_env)
		return (MALLOC_ERROR);
	new_env[new_env_size] = NULL;
	utils->size_env -= 1;
	utils->env = new_env;
	return (RETURN_SUCCESS);
}
