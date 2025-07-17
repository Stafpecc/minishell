/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:49:43 by stafpec           #+#    #+#             */
/*   Updated: 2025/07/17 13:45:09 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static long long	ft_atol(const char *nptr)
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

static int	overflow_check(char *arg, size_t counter_digits, bool negative_nbr,
		t_utils *utils)
{
	if (negative_nbr == TRUE)
	{
		if (counter_digits > 19 || (counter_digits == 19 && ft_atol(arg) >= 0))
			return (print_exit(NOT_NUM_ARG, arg, FALSE, utils));
	}
	else if (counter_digits > 19 || (counter_digits == 19 && ft_atol(arg) < 0))
		return (print_exit(NOT_NUM_ARG, arg, FALSE, utils));
	return (0);
}

// check for spaces char, then for 0 char
// once those are browsed we assign to our index
// the value of white_space_zero to check if the
// string is a valid input if it is go to overflow
// check for further processing

static int	check_arg_format(char *arg, bool *negative_nbr,
		size_t *counter_digits, t_utils *utils)
{
	size_t	index;

	index = 0;
	while (ft_isspace(arg[index]))
		index++;
	while (arg[index] == '0')
		index++;
	if (arg[index] == '-' || arg[index] == '+')
	{
		if (arg[index] == '-')
			*negative_nbr = TRUE;
		index++;
	}
	while (arg[index])
	{
		if (!ft_isdigit(arg[index]))
			return (print_exit(NOT_NUM_ARG, arg, FALSE, utils));
		index++;
		(*counter_digits)++;
	}
	return (0);
}

int	is_arg_digit_and_overflow(char *arg, t_utils *utils)
{
	bool	negative_nbr;
	size_t	counter_digits;
	int		return_value;

	return_value = 0;
	negative_nbr = FALSE;
	counter_digits = 0;
	return_value = check_arg_format(arg, &negative_nbr, &counter_digits, utils);
	if (return_value)
		return (return_value);
	return_value = overflow_check(arg, counter_digits, negative_nbr, utils);
	return (return_value);
}
