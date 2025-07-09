#include "../include/builtin.h"
#include "parsing.h"

// compare content of env to check if it hold
// the same name as the concerned arg entered with export

int	is_variable_already_in_env(t_utils *utils, char *variable_name,
		size_t i, bool is_equal)
{
	while (utils->env[i])
	{
		if (!ft_strncmp(variable_name, utils->env[i], ft_strlen(variable_name))
			&& (utils->env[i][ft_strlen(variable_name)] == '='))
		{
			if (is_equal)
				free(variable_name);
			return (i);
		}
		else
			i++;
	}
	if (is_equal)
		free(variable_name);
	return (FALSE);
}