/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stafpec <stafpec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:35:24 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/14 15:02:34 by stafpec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "return_error.h"

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

int	pwd_builtin(t_command_exec *node)
{
	char	*cwd;

	cwd = NULL;
	if (node->cmd_parts[1])
	{
		if (option_checker(node->cmd_parts))
			return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printfd("minishell: pwd: error retrieving current directory");
		ft_printfd(": getcwd: cannot access parent directories:");
		ft_printfd(" No such file or directory\n");
		return (RETURN_FAILURE);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	cwd = NULL;
	return (EXIT_SUCCESS);
}
