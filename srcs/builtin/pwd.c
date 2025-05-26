/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:35:24 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/26 17:03:23 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

// Check if we are dealing with an option or an argument.
static int	option_checker(char **cmd_parts)
{
	if (!ft_strncmp(cmd_parts[1], "-", 1) && cmd_parts[1][1])
	{
		ft_printfd("minishell: pwd: %c%c: invalid option\n", cmd_parts[1][0],
			cmd_parts[1][1]);
		return (2);
	}
	return (0);
}

// pwd_built check if it does received the double array
// that contain pwd + its potentials arguments
// then it check if there is options, if yes then return error
// if no then we get inside env to find the PWD line to print its
// content then return 0 else it would return 1
// TODL KEEP IN MIND J = 4!!!!!!!!

int	pwd_builtin(t_command_exec *node, t_utils *utils, int i, int j)
{
	j = 4;
	if (!node->cmd_parts || !node->cmd_parts[0])
		return (EXIT_FAILURE);
	if (node->cmd_parts[1])
	{
		if (option_checker(node->cmd_parts))
			return (2);
	}
	while (utils->env[i])
	{
		if (!ft_strncmp(utils->env[i], "PWD=", 4))
		{
			while (utils->env[i][j])
			{
				ft_printf("%c", utils->env[i][j]);
				j++;
			}
			ft_printf("\n");
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
