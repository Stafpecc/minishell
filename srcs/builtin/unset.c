/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:51:51 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/19 13:59:22 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

// clone the old_env into the cp_env that would be used
// to overwrite env with the right output
static char	**clone_env(t_utils *utils, char **cp_env, int index_overwrite)
{
	cp_env = malloc((utils->size_env + 1) * sizeof(char *));
	if (!cp_env)
		return (NULL);
	while (utils->env[index_overwrite])
	{
		cp_env[index_overwrite] = utils->env[index_overwrite];
		index_overwrite++;
	}
	cp_env[index_overwrite] = NULL;
	return (cp_env);
}

// check if the args match perfectly with the env line,
// if it does it mean we have to remove it
// so condense_env to remove a line dynamicaly and
// return true for further processing in
// unset_builtin we stay in the loop until we finished to browse all the args
static int	check_if_match(char **cmd, t_utils *utils, char **cp_env,
		size_t i_cp_env)
{
	int	i_args_chkr;

	i_args_chkr = 1;
	while (cmd[i_args_chkr])
	{
		if (!ft_strncmp(cp_env[i_cp_env], cmd[i_args_chkr],
				ft_strlen(cmd[i_args_chkr]))
			&& cp_env[i_cp_env][ft_strlen(cmd[i_args_chkr])] == '=')
		{
			if (condense_env(utils))
				return (MALLOC_ERROR);
			return (TRUE);
		}
		i_args_chkr++;
	}
	return (FALSE);
}
// overwrite the line in tmp_cp_env into the env to overwrite
// its old content

static void	write_case(t_utils *utils, char **tmp_cp_env,
		size_t *index_overwrite, size_t i_cp_env)
{
	utils->env[*index_overwrite] = tmp_cp_env[i_cp_env];
	*index_overwrite += 1;
}

// free ptr tmp_cp_env before exiting with the right code

static int	free_exit(char **tmp_cp_env, int return_value)
{
	if (tmp_cp_env)
		free(tmp_cp_env);
	return (return_value);
}

// we init the variables that would serve us to update our env
// accordingly to the args received here check if there is no arg
// if there is none just return_success do nothing tmp would
// now be assigned as a cp of the env in clone_env
// then we check if there is a match if there is none
// we write in the env the line that didnt matched with the arg
// repeat until the whole old_env is checked then go to free exit
// to free our ptr tmp_cp_env before leaving properly with the right
// code

int	unset_builtin(t_command_exec *node, t_utils *utils)
{
	char	**tmp_cp_env;
	int		match;
	size_t	i_cp_env;
	size_t	index_overwrite;

	index_overwrite = 0;
	i_cp_env = 0;
	match = FALSE;
	tmp_cp_env = NULL;
	if (!node->cmd_parts[1])
		return (RETURN_SUCCESS);
	tmp_cp_env = clone_env(utils, tmp_cp_env, 0);
	if (!tmp_cp_env)
		return (MALLOC_ERROR);
	while (tmp_cp_env[i_cp_env])
	{
		match = check_if_match(node->cmd_parts, utils, tmp_cp_env, i_cp_env);
		if (match == MALLOC_ERROR)
			return (free_exit(tmp_cp_env, MALLOC_ERROR));
		if (match == FALSE)
			write_case(utils, tmp_cp_env, &index_overwrite, i_cp_env);
		i_cp_env++;
	}
	return (free_exit(tmp_cp_env, RETURN_SUCCESS));
}
