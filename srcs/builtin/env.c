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
		ft_printfd("minishell: env: No arguments or options required\n");
		return (EXIT_FAILURE);
	}
	while (i != utils->size_env)
	{
		ft_printf("%s\n", utils->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
