/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:22:43 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/21 09:46:40 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ret_free_utils(int select, t_utils *utils)
{
	if (select >= 1)
		free_env(utils->env);
	if (select >= 2)
		free_av(utils->av);
	free(utils);
	return (RETURN_FAILURE);
}

static char **copy_av(char **av)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (av[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	while (j < i)
	{
		copy[j] = ft_strdup(av[j]);
		if (!copy[j])
		{
			while (j-- > 0)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

int	init_utils_struct(t_utils **utils, char **envp, char **av)
{
	*utils = malloc(sizeof(t_utils));
	if (!*utils)
		return (RETURN_FAILURE);
	(*utils)->env = copy_env(envp);
	if (!(*utils)->env)
		return (ret_free_utils(0, *utils));
	(*utils)->av = copy_av(av);
	if (!(*utils)->av)
		return (ret_free_utils(1, *utils));
	(*utils)->last_return = 0;
	(*utils)->num_nodes = 0;
	(*utils)->previous_pipes = -42;
	(*utils)->status = 0;
	(*utils)->type_of_first_arg = TOK_END;
	(*utils)->fd = -1;
	(*utils)->old_stdin = dup(STDIN_FILENO);
	if ((*utils)->old_stdin == -1)
		return (ret_free_utils(2, *utils));
	(*utils)->old_stdout = dup(STDOUT_FILENO);
	if ((*utils)->old_stdout == -1)
		return (ret_free_utils(2, *utils));
	(*utils)->size_env = ft_env_len((*utils)->env);
	(*utils)->run = 1;
	return (RETURN_SUCCESS);
}
