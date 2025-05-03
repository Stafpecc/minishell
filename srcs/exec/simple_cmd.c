/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:07:19 by ldevoude          #+#    #+#             */
/*   Updated: 2025/05/03 16:47:42 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

//we search and find the exercutable by trying all the path_dirs entrances

static char	*search_executable_in_paths(char **path_dirs, char *path_prefix,
    char *cmd_name, char *full_path)
{
int	i;

i = 0;
while (path_dirs[i])
{
    path_prefix = ft_strjoin(path_dirs[i], "/");
    if (!path_prefix)
        exit(-1);//return (free_arrays(NULL, path_dirs, cmd_name, NULL));
    full_path = ft_strjoin(path_prefix, cmd_name);
    if (!full_path)
        exit(-1);//return (free_arrays(NULL, path_dirs, cmd_name, path_prefix));
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

//we prepare everything to search the executable in the given path.
//by creating doubles array that will hold cmd, their parts and the
//diff path_dirs to search into until we find the right case
static char	*prepare_path_resolution(char *path, char *cmd)
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
    exit(-1);//return (free_arrays(path_dirs, NULL, NULL, NULL));
if (cmd_parts[0])
    cmd_name = strdup(cmd_parts[0]);
if (!cmd_name)
    exit(-1);//return (free_arrays(path_dirs, cmd_parts, NULL, NULL));
free_arrays(NULL, cmd_parts, NULL, NULL);
return (search_executable_in_paths(path_dirs, NULL, cmd_name, NULL));
}

//we search the PATH line in the env, once we found it
//we assign it to path then we prepare the resolution.
static char	*path_finder(char **env, char *cmd, char *path)
{
int		i;
char	*executable_in_paths;

executable_in_paths = NULL;
i = 0;
while (env[i] || !path)
{
    if (!strncmp(env[i], "PATH=", 5))
    {
        path = strdup(env[i]);
        if (path == NULL)
            return (NULL);
        executable_in_paths = prepare_path_resolution(path, cmd);
        free(path);
        break ;
    }
    i++;
}
return (executable_in_paths);
}

//Check if the user sent a cmd path or a cmd
//if cmd (like ls) it pass the first condition
//and go to find the path in path_finder
//else we go to childs_pathed_exec to handle that case

static void simple_cmd(char *input, char **env)
{
    char	*path;
	char	**separated_cmd_flags;

	if (!ft_strchr(input, '/'))
	{
		path = path_finder(env, input, NULL);
		if (path == NULL)
			exit(1);//child_error(-42, fd, 1, input);
		separated_cmd_flags = ft_split(input, ' ');
		if (!separated_cmd_flags)
		{
			free(path);
			exit(1);//child_error(-42, fd, 0, input);
		}
		execve(path, separated_cmd_flags, env);
		free_arrays(separated_cmd_flags, NULL, path, NULL);
		exit(-1);
	}
	else
		childs_pathed_exec(input, NULL);
}

//Init the child and pass it to simple_cmd for further processing
//while the parent wait for the child to complete its task (aka exec the simple cmd);
void init_simple_cmd (char *input, char **env)
{
    pid_t child;
    int status;
    
    env = NULL;
    input = NULL;
    child = fork();
    if (child == 0)
        exit(0);//simple_cmd(input, env);
    waitpid(child, &status, 0);
    return;
}