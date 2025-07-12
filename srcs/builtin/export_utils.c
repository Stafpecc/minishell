#include "../include/builtin.h"
#include "parsing.h"

// compare content of env to check if it hold
// the same name as the concerned arg entered with export

int	is_variable_already_in_env(t_utils *utils, char *variable_name,
		size_t i, bool is_equal)
{
    int len;

    len = ft_strlen(variable_name);
	while (utils->env[i])
	{
        if (!ft_strncmp(variable_name, utils->env[i], len) &&
			(utils->env[i][len] == '=' || utils->env[i][len] == '\0'))
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

// utils function that isolate the name of the variable
// in case of a cmd with an = sign, for further processing
// in equal_sign_case
// increment index until we get to the =sign, malloc
// enough space to variable_name thanks to that index then fill
// the same variable with the rightful characters then return the result

char	*assign_variable_name(char *cmd, char *variable_name, size_t i,
		size_t j)
{
	while (cmd[i] != '=')
		i++;
	variable_name = malloc(i + 1 * sizeof(char));
	if (!variable_name)
		return (NULL);
	while (j != i)
	{
		variable_name[j] = cmd[j];
		j++;
	}
	variable_name[j] = '\0';
	return (variable_name);
}