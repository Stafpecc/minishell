/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:46:51 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/24 11:31:28 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// to check if we got a right parameters
//+ if we need a new line or not
static int	is_newline(t_command_exec *node, int i, bool *newline, int *index_print)
{
	if (!node->cmd_parts || !node->cmd_parts[0])
		return (1);
	if (node->cmd_parts[1] && ft_strncmp(node->cmd_parts[1], "-n", 2) == 0 )
	{
		*newline = FALSE;
		*index_print = 2;
		while(node->cmd_parts[1][i])
		{
			printf("chier dans les lasagnes\n");
			if(!node->cmd_parts[1][i])
				break;
			if (node->cmd_parts[1][i] == 'n')
				i += 1;
			else 
			{
				*index_print = 1;
				*newline = TRUE;
				break;
			}
		}
	}
	//TODO a checker to see if there is more tag -n after that one
	return (0);
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
