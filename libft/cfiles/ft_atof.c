/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:11:22 by tarini            #+#    #+#             */
/*   Updated: 2025/02/28 16:30:18 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_number(const char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else if (str[i] == '.' && dot_count == 0)
		{
			dot_count++;
			i++;
		}
		else
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int	get_sign(const char *str, int *i, int sign)
{
	if (str[*i] == '-')
		sign = -1;
	(*i)++;
	return (sign);
}

double	ft_atof(const char *str)
{
	double	result;
	double	fraction;
	int		sign;
	int		i;

	if (!is_valid_number(str))
		exit(EXIT_FAILURE);
	result = 0.0;
	fraction = 1.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = get_sign(str, &i, sign);
	}
	while (ft_isdigit(str[i]))
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
	{
		fraction /= 10.0;
		result += (str[i++] - '0') * fraction;
	}
	return (result * sign);
}
