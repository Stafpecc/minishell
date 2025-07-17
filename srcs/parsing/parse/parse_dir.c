/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:31:59 by tarini            #+#    #+#             */
/*   Updated: 2025/07/17 13:32:41 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//#include "../../../libft/includes/libft.h"

//#include <stdbool.h>
#include <dirent.h>

/*
Function that:
- tries to open the given path as a directory;
- if the opening succeeds, closes the directory and returns true;
- otherwise returns false, indicating it is not a directory.
*/
bool	is_directory(const char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (true);
	}
	return (false);
}

int	parse_directory(t_command *curr, t_utils *utils)
{
	const char	*arg;

	if (!curr || !curr->cmd_parts || !curr->cmd_parts[0])
		return (RETURN_SUCCESS);
	arg = curr->cmd_parts[0]->arg;
	if (is_directory(arg))
	{
		ft_printfd("minishell: %s: Is a directory\n", arg);
		utils->last_return = CMD_PERMISSION_DENIED;
		return (RETURN_FAILURE);
	}
	if (ft_strchr(arg, '/'))
	{
		if (check_file(arg, utils, FILE_EXEC) == RETURN_FAILURE)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
