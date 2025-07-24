/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:23:39 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/17 16:15:44 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	*search_executable_in_paths(char **path_dirs, char *path_prefix,
		char *cmd_name, char *full_path)
{
	int	i;

	i = 0;
	while (path_dirs[i])
	{
		path_prefix = ft_strjoin(path_dirs[i], "/");
		if (!path_prefix)
			return (free_arrays(NULL, path_dirs, cmd_name, NULL));
		full_path = ft_strjoin(path_prefix, cmd_name);
		if (!full_path)
			return (free_arrays(NULL, path_dirs, cmd_name, path_prefix));
		free(path_prefix);
		if (!access(full_path, X_OK))
		{
			free_arrays(path_dirs, NULL, cmd_name, NULL);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_arrays(path_dirs, NULL, cmd_name, NULL);
	return (NULL);
}

char	*prepare_path_resolution(char *path, char *cmd)
{
	char	**path_dirs;
	char	**cmd_parts;
	char	*cmd_name;

	cmd_name = NULL;
	path_dirs = ft_split(path, ':');
	if (!path_dirs)
		return (NULL);
	cmd_parts = ft_split(cmd, ' ');
	if (!cmd_parts || !path_dirs)
		return (free_arrays(path_dirs, NULL, NULL, NULL));
	if (cmd_parts[0])
		cmd_name = ft_strdup(cmd_parts[0]);
	if (!cmd_name)
		return (free_arrays(path_dirs, cmd_parts, NULL, NULL));
	free_arrays(NULL, cmd_parts, NULL, NULL);
	return (search_executable_in_paths(path_dirs, NULL, cmd_name, NULL));
}

char	*path_finder(char **env, char *cmd, char *path)
{
	int		i;
	char	*executable_in_paths;

	executable_in_paths = "DEFAULT";
	i = 0;
	if (env)
	{
		while (env[i] && !path)
		{
			if (env[i] && (!ft_strncmp(env[i], "PATH=", 5)))
			{
				path = ft_strdup(env[i]);
				if (path == NULL)
				{
					return (NULL);
				}
				executable_in_paths = prepare_path_resolution(path, cmd);
				free(path);
				return (executable_in_paths);
			}
			i++;
		}
	}
	return (executable_in_paths);
}

char	*free_arrays(char **one, char **two, char *three, char *four)
{
	int	i;

	if (one)
	{
		i = 0;
		while (one[i])
			free(one[i++]);
		free(one);
	}
	if (two)
	{
		i = 0;
		while (two[i])
			free(two[i++]);
		free(two);
	}
	free(three);
	free(four);
	return (NULL);
}
// close what is not set to NONE
// and also set them to NONE

int	close_and_set_none(int previous_pipe, int *pipe_fd)
{
	if (previous_pipe != NONE)
	{
		if (close(previous_pipe) == -1)
			return (RETURN_FAILURE);
		previous_pipe = NONE;
	}
	if (pipe_fd[0] != NONE)
	{
		if (close(pipe_fd[0]) == -1)
			return (RETURN_FAILURE);
		pipe_fd[0] = NONE;
	}
	if (pipe_fd[1] != NONE)
	{
		if (close(pipe_fd[1]) == -1)
			return (RETURN_FAILURE);
		pipe_fd[1] = NONE;
	}
	return (RETURN_SUCCESS);
}
