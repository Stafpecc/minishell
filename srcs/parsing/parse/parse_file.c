/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:36 by tarini            #+#    #+#             */
/*   Updated: 2025/07/16 14:58:35 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

#include <errno.h>

/*
	Checks the existence and access rights of a file 
	according to the specified mode.
	Displays an error message on failure and updates the return code.
	Returns RETURN_SUCCESS if everything is OK, otherwise RETURN_FAILURE.
*/
int	check_file(const char *path, t_utils *utils, t_file_mode mode)
{
	(void) mode;
	if (!path)
		return (RETURN_FAILURE);
	if (access(path, F_OK) != 0)
	{
		if (errno == ENOENT)
			ft_printfd("minishell: %s: No such file or directory\n", path);
		else
		{
			ft_printfd("minishell: ");
			perror(path);
		}
		utils->last_return = CMD_INVALID_ARGUMENT;
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
