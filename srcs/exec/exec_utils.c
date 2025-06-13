

#include "../../include/exec.h"

// Just check if the cmd we are dealing with are a built-in cmd or not
// if yes return TRUE if no return FALSE

bool	built_in_checker(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo"))
		return (true);
	else
		return (false);
}

// To count how much commands has been sent
// return the value of how much cmd
// in the user's input
int	count_commands(t_command_exec *cmds)
{
	int counter_cmd;

	counter_cmd = 0;
	while (cmds)
	{
		counter_cmd++;
		cmds = cmds->next;
	}
	return (counter_cmd);
}

size_t	ft_env_len(char **env)
{
	size_t	len = 0;

	while (env && env[len])
		len++;
	return (len);
}

int	expand_env(t_utils *utils)
{
	size_t	old_size = ft_env_len(utils->env);
	size_t	new_size = old_size + 2; // +1 pour nouveau slot, +1 pour NULL final
	char	**new_env;

	new_env = ft_realloc(utils->env, sizeof(char *) * new_size);
	if (!new_env)
		return (RETURN_FAILURE);

	new_env[old_size] = NULL; // nouvelle entrée vide
	new_env[old_size + 1] = NULL; // fin
	utils->env = new_env;
	return (RETURN_SUCCESS);
}

