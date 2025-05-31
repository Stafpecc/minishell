
//#include "../include/exec.h"
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
cmd_parts = ft_split(cmd, ' '); //MAY BE USELESS BCS OF OUR DOUBLE ARRAY
if (!cmd_parts || !path_dirs)
    return (free_arrays(path_dirs, NULL, NULL, NULL));
if (cmd_parts[0]) //SAME
    cmd_name = ft_strdup(cmd_parts[0]);
if (!cmd_name) //SAME Lel
    return (free_arrays(path_dirs, cmd_parts, NULL, NULL));
free_arrays(NULL, cmd_parts, NULL, NULL);
return (search_executable_in_paths(path_dirs, NULL, cmd_name, NULL));
}

char	*path_finder(char **env, char *cmd, char *path)
{
    int		i;
    char	*executable_in_paths;

    executable_in_paths = NULL;
    i = 0;
    while (env[i] || !path)
    {
        if (!ft_strncmp(env[i], "PATH=", 5))
        {
            path = ft_strdup(env[i]);
            if (path == NULL)
            {
                return (NULL);
            }
            executable_in_paths = prepare_path_resolution(path, cmd);
            free(path);
            break ;
        }
        i++;
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

void	child_error(int infile, int *fd, int error, char *cmd)
{
//cmd = NULL; //TORM
if (error == 1)
{
    ft_printfd("%s: command not found\n", cmd);
    exit(127);
}
if (infile >= 0)
    close(infile);
if (fd[1])
    close(fd[1]);
if (fd[0])
    close(fd[0]);
ft_printfd("test\n");
if (infile == -42)
{
    ft_printfd("test\n");
    exit(0);
}
ft_printfd("test\n");

exit(-255);
}