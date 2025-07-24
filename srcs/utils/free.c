/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:13:04 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/21 09:55:10 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

void	free_av(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_utils(t_utils *utils)
{
	free_env(utils->env);
	if (utils->fd != -1)
		close(utils->fd);
	if (utils->old_stdin != -1)
		close(utils->old_stdin);
	if (utils->old_stdout != -1)
		close(utils->old_stdout);
	free_av(utils->av);
	free(utils);
}
