/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:37:08 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 16:14:39 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// Check if we are dealing with an option or an argument.
static int	option_checker(char **cmd_parts)
{
	if (!ft_strncmp(cmd_parts[1], "-", 1) && cmd_parts[1][1])
	{
		if (join_err_msg_and_write("minishell: pwd: ", cmd_parts[1],
				": invalid option\n"))
			return (MALLOC_ERROR);
		return (2);
	}
	return (0);
}

// pwd_built check if it does received the double array
// that contain pwd + its potentials arguments
// then it check if there is options, if yes then return error
// if no then we get inside env to find the PWD line to print its
// content then return 0 else it would return 1

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
		if (join_err_msg_and_write("minishell: pwd:",
				" errror retrieving current directory: getcwd: cannot access ",
				"parent directories: No such file or directory\n"))
			return (MALLOC_ERROR);
		return (RETURN_FAILURE);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	cwd = NULL;
	return (EXIT_SUCCESS);
}
