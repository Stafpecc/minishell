/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:33:15 by ldevoude          #+#    #+#             */
/*   Updated: 2025/06/24 10:33:59 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <stdio.h>

// print exit like bash does then print the right message if needed
// then we exit with the right code!
// TODO do not exit yet free what need to be freed THEN exit
static int	print_exit(long long code, char *arg, bool too_many_arguments)
{
	ft_printfd("exit\n");
	if (code == NOT_NUM_ARG)
		ft_printfd("minishell: exit: %s: numeric argument required\n", arg);
	if (too_many_arguments)
	{
		ft_printfd("minishell: exit: too many arguments\n");
		return (RETURN_FAILURE);
	}
	exit(code);
}

long long static	ft_atol(const char *nptr)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!ft_strncmp(nptr, "-9223372036854775808", 21))
	{
		return (-9223372036854775807);
	}
	i = ft_pass(i, nptr, &sign);
	while (ft_isdigit(nptr[i]))
	{
		if ((result * 10 + (nptr[i] - '0')) / 10 != result)
			return (-1 * (sign > 0));
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

// pass the parsed arg to the ft_atol and depending of if is
// a negative number or a positive one then the overflow check
// would be slighty different. if our arg pass that test it mean
// it passed all the necessary test so we can continue in exit_built_in
static void	overflow_check(char *arg, size_t counter_digits, bool negative_nbr)
{
	if (negative_nbr == TRUE)
	{
		if (counter_digits > 19 || (counter_digits == 19 && ft_atol(arg) >= 0))
			print_exit(NOT_NUM_ARG, arg, FALSE);
	}
	else if (counter_digits > 19 || (counter_digits == 19 && ft_atol(arg) < 0))
		print_exit(NOT_NUM_ARG, arg, FALSE);
}
// check for spaces char, then for 0 char
// once those are browsed we assign to our index
// the value of white_space_zero to check if the
// string is a valid input if it is go to overflow
// check for further processing

static void	is_arg_digit_and_overflow(char *arg, bool negative_nbr,
		size_t white_space_zero, size_t counter_digits)
{
	size_t	index_check_isdigit;

	while (ft_isspace(arg[white_space_zero]))
		white_space_zero++;
	while (arg[white_space_zero] == '0')
		white_space_zero++;
	index_check_isdigit = white_space_zero;
	if (arg[index_check_isdigit - 1] != '0' && (arg[index_check_isdigit] == '-'
			|| arg[index_check_isdigit] == '+'))
	{
		if (arg[index_check_isdigit] == '-')
			negative_nbr = TRUE;
		index_check_isdigit++;
	}
	while (arg[index_check_isdigit])
	{
		if (!ft_isdigit(arg[index_check_isdigit]))
			print_exit(NOT_NUM_ARG, arg, FALSE);
		index_check_isdigit++;
		counter_digits++;
	}
	overflow_check(arg, counter_digits, negative_nbr);
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
		print_exit(utils->last_return, NULL, FALSE);
	is_arg_digit_and_overflow(node->cmd_parts[1], FALSE, 0, 0);
	if (node->cmd_parts[2])
		return (print_exit(0, NULL, TRUE));
	return_value = ft_atoi(node->cmd_parts[1]);
	if (return_value < 0)
		print_exit(return_value + 256, NULL, FALSE);
	else
		print_exit(return_value - 256, NULL, FALSE);
	return (RETURN_SUCCESS);
}
