/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:43 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/26 13:10:25 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static char	**ret_free_env(char **new_env)
{
	free_env(new_env);
	return (NULL);
}

static char	**add_var_to_env(char **env, const char *var)
{
	int		i;
	char	**new_env;

	i = 0;
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
			return (ret_free_env(new_env));
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		return (ret_free_env(new_env));
	new_env[i + 1] = NULL;
	free_env(env);
	return (new_env);
}

static t_utils	*ret_free_utils(int select, t_utils *utils)
{
	if (select == 1)
		free_env(utils->env);
	free(utils);
	return (NULL);
}

t_utils	*init_utils_struct(char **envp)
{
	t_utils	*utils;
	char	**tmp;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		return (NULL);
	utils->env = copy_env(envp);
	if (!utils->env)
		return (ret_free_utils(0, utils));
	tmp = add_var_to_env(utils->env, "MINISHELL_RUNNING=1");
	if (!tmp)
		return (ret_free_utils(1, utils));
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
