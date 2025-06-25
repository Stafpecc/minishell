/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:43 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/25 18:22:59 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static char **add_var_to_env(char **env, const char *var)
{
	int		i = 0;
	char	**new_env;

	while (env && env[i])
		i++;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);

	i = 0;
	while (env && env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
	{
		free_env(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	free_env(env);
	return (new_env);
}


static t_utils *init_utils_struct(char **envp)
{
	t_utils *utils = malloc(sizeof(t_utils));
	char **tmp;

	if (!utils)
		return (NULL);

	utils->env = copy_env(envp);
	if (!utils->env)
	{
		free(utils);
		return (NULL);
	}
	tmp = add_var_to_env(utils->env, "MINISHELL_RUNNING=1");
	if (!tmp)
	{
		free_env(utils->env);
		free(utils);
		return (NULL);
	}
	utils->env = tmp;
	utils->last_return = 0;
	utils->num_nodes = 0;
	utils->previous_pipes = -42;
	utils->status = 0;
	utils->type_of_first_arg = TOK_END;
	utils->old_stdin = dup(STDIN_FILENO); //TODO PROTECT
	utils->old_stdout = dup(STDOUT_FILENO); //TODO PROTECT
	utils->size_env = ft_env_len(utils->env);

	return (utils);
}