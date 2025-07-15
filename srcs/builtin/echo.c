
#include "../include/builtin.h"
#include "parsing.h"
#include "return_error.h"

#define NO_FLAG_N 1
#define FLAG_N 0
//here we check if there is any -n flag that follow
//the first one that has been validated in is_newline
//it updated index_print if it found a new valid -n 
//array of chars
static bool	pass_n_flags(t_command_exec *node, int *index_print, int i)
{
	if (!node->cmd_parts[*index_print])
		return (RETURN_SUCCESS);
	while (node->cmd_parts[*index_print]
		&& ft_strncmp(node->cmd_parts[*index_print], "-n", 2) == 0)
	{
		while (node->cmd_parts[*index_print][i])
		{
			if (node->cmd_parts[1][i] == 'n')
				i++;
			else
				break ;
		}
		i = 2;
		*index_print += 1;
	}
	return (RETURN_SUCCESS);
}

// to check if we got a right parameters
// update the ptr newline if we need a new line or not
// and index_print depending of the situation
// if there was a valid n parameter then we also
// return pass_n_flag to ignore all n flags that follow up
static bool	is_newline(t_command_exec *node, int i, bool *newline,
	int *index_print)
{
	if (!node->cmd_parts || !node->cmd_parts[0])
		return (RETURN_FAILURE);
	if (node->cmd_parts[1] && ft_strncmp(node->cmd_parts[1], "-n", 2)
		== 0)
	{
		*newline = FALSE;
		*index_print = 2;
		while (node->cmd_parts[1][i])
		{
			if (node->cmd_parts[1][i] == 'n')
				i += 1;
			else
			{
				*index_print = 1;
				*newline = TRUE;
				return (RETURN_SUCCESS);
			}
		}
	}
	return (pass_n_flags(node, index_print, 2));
}

// check if we received the right cmd and
// if it is valid + if we received the -n
// flag to setup or bool newline and index i
// then we print the whole content of our cmd

// TODO change t_command *node into simple a char **cmd
// if we do not need the whole struct
int	echo_builtin(t_command_exec *node, bool newline, int i)
{
	if (is_newline(node, 2, &newline, &i) == 1)
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
	if (newline == TRUE)
	{
		if (write(STDOUT_FILENO, "\n", 1) < 0)
			return (1);
	}
	return (0);
}
