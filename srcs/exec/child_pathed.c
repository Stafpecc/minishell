//#include "../include/exec.h"
#include "../../include/exec.h"

void	childs_pathed_exec_failed(char **split_args, char **split_result,
    char *path, char **result)
{
int	i;

free_arrays(split_result, split_args, path, NULL);
i = 0;
while (result[i])
{
    free(result[i]);
    i++;
}
free(result);
exit(-1);
}

// exec_cmd
void	childs_pathed_exec_final(char **split_args, char **split_result,
    char *path, int *fd)
{
char	**result;
int		i;
int		fd_test_perms;

i = 0;
while (split_args[i])
    i++;
result = ft_split(split_args[i - 1], ' ');
if (!result)
{
    free_arrays(split_result, split_args, path, NULL);
    child_error(-42, fd, 0, NULL);
}
if (access(split_result[0], F_OK) != 0)
{
    //ft_printfd("no such file or directory: %s\n", split_result[0]);
}
fd_test_perms = open(split_result[0], O_RDONLY | __O_DIRECTORY);
if (fd_test_perms >= 0)
{
    close(fd_test_perms);
    //ft_printfd("permission denied : %s\n", split_result[0]);
}
execve(split_result[0], result, NULL);
childs_pathed_exec_failed(split_args, split_result, path, result);
}

// Analyze path ?
void	childs_pathed_exec(char *cmd, int *fd, char *path)
{
char	**split_result;
char	**split_args;

path = ft_strdup(cmd);
if (!path)
    child_error(-42, fd, 0, NULL);
split_result = ft_split(path, ' ');
if (!split_result)
{
    free(path);
    child_error(-42, fd, 0, NULL);
}
split_args = ft_split(cmd, '/');
if (!split_args)
{
    free_arrays(split_result, NULL, path, NULL);
    child_error(-42, fd, 0, NULL);
}
childs_pathed_exec_final(split_args, split_result, path, fd);
}