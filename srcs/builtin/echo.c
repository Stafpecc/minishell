#include "../include/builtin.h"

// to check if we got a right parameters
//+ if we need a new line or not
int	is_newline(t_command_exec *node, int *i, bool *newline)
{
	if (!node->cmd_parts || !node->cmd_parts[0])
		return (1);
	if (node->cmd_parts[1] && ft_strcmp(node->cmd_parts[1], "-n") == 0)
	{
		*newline = false;
		*i = 2;
	}
	else
	{
		*newline = true;
		*i = 1;
	}
	return (0);
}

// check if we received the right cmd and
// if it is valid + if we received the -n
// flag to setup or bool newline and index i
// then we print the whole content of our cmd

//TODO change t_command *node into simple a char **cmd
//if we do not need the whole struct
int	echo_builtin(t_command_exec *node, bool newline, int i)
{
	if (is_newline(node, &i, &newline) == 1)
		return (1);
	if (!node->cmd_parts[1])
	{
		if (write(STDOUT_FILENO, "\n", 1) < 0)
			return (1);
		return (0);
	}
	while (node->cmd_parts[i])
	{
		if (ft_printf("%s", node->cmd_parts[i]) < 0)
			return (1);
		i++;
		if (node->cmd_parts[i])
		{
			if (ft_printf(" ") < 0)
				return (1);
		}
	}
	if (newline == true)
	{
		if (write(STDOUT_FILENO, "\n", 1) < 0)
			return (1);
	}
	return (0);
}