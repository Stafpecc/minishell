/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:44:14 by ldevoude          #+#    #+#             */
/*   Updated: 2025/07/21 09:33:19 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

// here we check if there is any -n flag that follow
// the first one that has been validated in is_newline
// it update index_print if it find a new valid -n 
// array of chars until it doesnt anymore

static bool	pass_n_flags(t_command_exec *node, int *index_print, int i)
{
	bool	get_out;

	get_out = FALSE;
	if (!node->cmd_parts[*index_print])
		return (RETURN_SUCCESS);
	while (node->cmd_parts[*index_print]
		&& ft_strncmp(node->cmd_parts[*index_print], "-n", 2) == 0)
	{
		while (node->cmd_parts[*index_print][i])
		{
			if (node->cmd_parts[*index_print][i] == 'n')
				i++;
			else
			{
				get_out = TRUE;
				break ;
			}
		}
		if (get_out == TRUE)
			break ;
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

// check if we received the right cmd +
// if it is valid + if we received the -n
// flag to setup our bool newline and index i
// then we print the whole content of our cmd

int	echo_builtin(t_command_exec *node, bool newline, int i)
{
	if (!node->cmd_parts[1])
	{
		if (write(STDOUT_FILENO, "\n", 1) < 0)
			return (1);
		return (0);
	}
	if (is_newline(node, 2, &newline, &i) == 1)
		return (1);
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
