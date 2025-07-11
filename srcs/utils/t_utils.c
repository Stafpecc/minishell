/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:43 by stafpec           #+#    #+#             */
/*   Updated: 2025/06/26 16:35:21 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "exec.h"

static t_utils	*ret_free_utils(int select, t_utils *utils)
{
	if (select == 1)
		free_env(utils->env);
	free(utils);
	return (NULL);
}
//utils struct would be used to hold the information
//that would be necessary for our program
//like to hold the last return value
//or the env of our minishell or how
//much nodes we have during the process of the user's prompt
t_utils	*init_utils_struct(char **envp)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (!utils)
		return (NULL);
	utils->env = copy_env(envp);
	if (!utils->env)
		return (ret_free_utils(0, utils));
	utils->last_return = 0;
	utils->num_nodes = 0;
	utils->previous_pipes = -42;
	utils->status = 0;
	utils->type_of_first_arg = TOK_END;
	utils->old_stdin = dup(STDIN_FILENO); //TODO PROTECT
	utils->old_stdout = dup(STDOUT_FILENO); //TODO PROTECT
	utils->size_env = ft_env_len(utils->env);
	utils->run = 1;
	return (utils);
}
