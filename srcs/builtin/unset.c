

#include "builtin.h"
#include "minishell.h"

static void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static bool	cmp_args_with_env_line(char **args, char *env_line)
{
	int		i;
	size_t	len;

	len = 0;
	i = 1;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		if (!ft_strncmp(env_line, args[i], len) && env_line[len] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	unset_builtin(t_command_exec *node, t_utils *utils, size_t i, size_t j)
{
	char	**new_env;

	if (!node->cmd_parts[1])
		return (RETURN_SUCCESS);
	new_env = malloc(sizeof(char *) * (utils->size_env + 1));
	if (!new_env)
		return (MALLOC_ERROR);
	while (utils->env[i])
	{
		if (!cmp_args_with_env_line(node->cmd_parts, utils->env[i]))
		{
			new_env[j] = ft_strdup(utils->env[i]);
			if (!new_env[j])
				return (free_array(new_env), MALLOC_ERROR);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	free_array(utils->env);
	utils->env = new_env;
	utils->size_env = j;
	return (RETURN_SUCCESS);
}
