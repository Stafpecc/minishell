/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevoude <ldevoude@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:54:30 by tarini            #+#    #+#             */
/*   Updated: 2025/06/24 08:10:16 by ldevoude         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	i = ft_pass(i, nptr, &sign);
	while (ft_isdigit(nptr[i]))
	{
		if ((result * 10 + (nptr[i] - '0')) / 10 != result)
			return (-1 * (sign > 0));
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)result * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av) {
	(void)ac;
    int i = atoi(av[1]);
	int y = ft_atoi(av[1]);
 
    printf("with atoi function       :  %d\n", i);
	printf("with 42 atoi function    :  %d\n", y);
	return 0;
}
*/