/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:48:28 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/16 10:31:24 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	env_builtin(t_command_exec *node, t_utils *utils, size_t i)
{
	i = 0;
	if (node->cmd_parts[1])
	{
		if (join_err_msg_and_write("minishell: env: '", node->cmd_parts[1],
				"': No arguments or options required\n"))
			return (MALLOC_ERROR);
		return (EXIT_FAILURE);
	}
	if (utils->env)
	{
		while (utils->env[i])
		{
			if (ft_strchr(utils->env[i], '='))
				ft_printf("%s\n", utils->env[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
