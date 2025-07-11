/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:48:28 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/22 15:22:16 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"


int	env_builtin(t_command_exec *node, t_utils *utils, size_t i)
{
	i = 0;
	if (node->cmd_parts[1])
	{
		ft_printfd("minishell: env: '%s': No arguments or options required\n", node->cmd_parts[1]);
		return (EXIT_FAILURE);
	}
	if(utils->env)
	{
		while (utils->env[i])
		{
			if(ft_strchr(utils->env[i], '='))
				ft_printf("%s\n", utils->env[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
