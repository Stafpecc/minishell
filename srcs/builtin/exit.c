/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:39:12 by tarini            #+#    #+#             */
/*   Updated: 2025/07/20 11:38:05 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print exit like bash does then print the right message if needed
// then we exit with the right code!

int	print_exit(long long code, char *arg, bool too_many_arguments,
		t_utils *utils)
{
	if (utils->num_nodes == 1)
		ft_printfd("exit\n");
	if (code == NOT_NUM_ARG)
	{
		utils->run = 0;
		if (join_err_msg_and_write("minishell: exit: ", arg,
				" numeric argument required\n"))
			return (MALLOC_ERROR);
		return (NOT_NUM_ARG);
	}
	if (too_many_arguments)
	{
		if (join_err_msg_and_write("minishell:", " exit: ",
				"too many arguments\n"))
			return (MALLOC_ERROR);
		return (RETURN_FAILURE);
	}
	utils->run = 0;
	return (code);
}

// exit_builtin would check if we at least have an arg
// if not like bash we exit with the last return
// then we check if our first arg is a digit
// and if it does overflow
// then we check if there is more than a single arg
// if yes then return failure and get back to
// minishell prompt
// we save the result of ft_atoi into exit_value

unsigned int	exit_builtin(t_command_exec *node, t_utils *utils)
{
	long long	return_value;

	return_value = 0;
	if (!node->cmd_parts[1])
	{
		ft_printfd("exit\n");
		utils->run = 0;
		return (utils->last_return);
	}
	return_value = is_arg_digit_and_overflow(node->cmd_parts[1], utils);
	if (return_value)
		return (return_value);
	if (node->cmd_parts[2])
		return (print_exit(0, NULL, TRUE, utils));
	if (return_value == 0)
	{
		return_value = ft_atoi(node->cmd_parts[1]);
		return (print_exit(return_value + 256, NULL, FALSE, utils));
	}
	else
		return (print_exit(return_value % 256, NULL, FALSE, utils));
}
